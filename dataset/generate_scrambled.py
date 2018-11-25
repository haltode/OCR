import random

random.seed(42)

charset = ("abcdefghijklmnopqrstuvwxyz"
           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
           "0123456789"
           ".,")
repeat_char = 2000

out = []
for c in charset:
    out += [c] * repeat_char
random.shuffle(out)

# Creates two files:
#   - 'scrambled.txt' as a simple transcript (used by the OCR during training)
#   - 'scrambled.tex' as a formated transcript (used to generate the pdf)
cnt = 0
with open('scrambled.txt', 'w') as txt, open('scrambled.tex', 'w') as tex:
    for c in out:
        txt.write(c), tex.write(c)
        cnt += 1
        # Indent (80 chars / line)
        if cnt % 80 == 0:
            txt.write('\n'), tex.write('\n')
        # Page break (4000 chars / page)
        if cnt % 4000 == 0:
            cnt = 0
            txt.write('\n\n'), tex.write('\n\\newpage\n')

print("charset size:", len(charset))
print("total chars generated:", repeat_char * len(charset))
print(repeat_char, "times per char")
