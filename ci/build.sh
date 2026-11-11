#!/bin/sh
# BolumNN altindaki her C programini derler ve calistirir.
# Butun hatalari toplar (ilk hatada durmaz). Hatalar workflow annotation olarak
# basilir; boylece GitHub'a giris yapmadan da okunabilir.
#
#   CC=gcc sh ci/build.sh
#   CC=clang SAN=1 sh ci/build.sh      # AddressSanitizer + UBSan (sizinti dahil)
#
# Program bicimleri:
#   BolumNN/ad.c        tek dosyalik program
#   BolumNN/ad/         klasordeki butun .c dosyalari tek program olarak derlenir
# Ilk satirinda "CALISTIRMA: yalniz derleme" yazan dosya (ya da klasordeki main
# dosyasi) yalnizca derlenir.
set -u
CC="${CC:-gcc}"
CFLAGS="-std=c11 -Wall -Wextra -pedantic -O1 -g"
[ "$CC" = "gcc" ] && CFLAGS="$CFLAGS -Werror"
[ "${SAN:-0}" = "1" ] && CFLAGS="$CFLAGS -fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover=all"
LIBS="-lm"
summary="${GITHUB_STEP_SUMMARY:-/dev/stdout}"
label="${RUNNER_OS:-local}/$CC"
[ "${SAN:-0}" = "1" ] && label="$label+asan"
tmp=$(mktemp -d)
failed=""
ok=0

printf '\n## C programlari — %s\n\n| Program | Sonuc |\n|---|---|\n' "$label" >> "$summary"

for p in Bolum*/*.c Bolum*/*/; do
    [ -e "$p" ] || continue
    p=${p%/}
    if [ -d "$p" ]; then
        srcs=$(ls "$p"/*.c 2>/dev/null)
        [ -n "$srcs" ] || continue
        first=$(grep -l 'int main' $srcs | head -1)
        incl="-I$p"
    else
        srcs="$p"
        first="$p"
        incl=""
    fi
    name=$(echo "$p" | tr '/.' '__')
    exe="$tmp/$name"
    if ! $CC $CFLAGS $incl $srcs -o "$exe" $LIBS > "$tmp/$name.log" 2>&1; then
        failed="$failed $p"
        printf '| `%s` | **DERLENMEDI** |\n' "$p" >> "$summary"
        continue
    fi
    if [ -n "$first" ] && head -1 "$first" | grep -q 'CALISTIRMA: yalniz derleme'; then
        ok=$((ok + 1))
        printf '| `%s` | derlendi |\n' "$p" >> "$summary"
        continue
    fi
    run="$tmp/run_$name"
    mkdir -p "$run"
    if (cd "$run" && timeout 20 "$exe" < /dev/null > "$tmp/$name.out" 2>&1); then
        ok=$((ok + 1))
        printf '| `%s` | ok |\n' "$p" >> "$summary"
    else
        rc=$?
        { echo "cikis kodu $rc"; tail -25 "$tmp/$name.out"; } >> "$tmp/$name.log"
        failed="$failed $p"
        printf '| `%s` | **CALISMADI (%s)** |\n' "$p" "$rc" >> "$summary"
    fi
    leftover=$(ls -A "$run")
    if [ -n "$leftover" ]; then
        failed="$failed $p"
        echo "geride kalan dosyalar: $leftover" >> "$tmp/$name.log"
        printf '| `%s` | **DOSYA BIRAKTI** |\n' "$p" >> "$summary"
    fi
done

[ -z "$failed" ] && { printf '\n%s programin hepsi %s uzerinde basarili.\n' "$ok" "$label"; exit 0; }

printf '\n### Hatalar\n' >> "$summary"
for p in $failed; do
    name=$(echo "$p" | tr '/.' '__')
    printf '\n<details><summary>%s</summary>\n\n```\n' "$p" >> "$summary"
    head -40 "$tmp/$name.log" >> "$summary"
    printf '```\n\n</details>\n' >> "$summary"
done

# Hatalari tek annotation'da topla (satir sonlari %0A olarak kodlanir).
msg=$(for p in $failed; do
        name=$(echo "$p" | tr '/.' '__')
        printf '%s:\n' "$p"
        grep -E 'error|warning|cikis kodu|geride kalan|undefined reference|ERROR: |runtime error|SUMMARY' "$tmp/$name.log" \
            | head -4 | sed 's/^/  /'
      done | sed 's/%/%25/g' | awk '{printf "%s%%0A", $0}')
printf '::error title=Bolum programlari %s uzerinde basarisiz::%s\n' "$label" "$msg"

printf '\nBasarisiz:%s\n' "$failed"
exit 1
