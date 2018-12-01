import random

random.seed(42)

charset = ("abcdefghijklmnopqrstuvwxyz"
           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
           ".,")
repeat_char = 1750

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
        txt.write(c)
        # Special characters to escape in LaTeX
        if c in ".,":
            c = '{' + c + '}'
        tex.write(c)
        cnt += 1
        # Indent
        if cnt % 62 == 0:
            txt.write('\n')
            tex.write('\\\\\n')
        # Page break
        if cnt % 3500 == 0:
            cnt = 0
            txt.write('\n\n')
            tex.write('\n\\newpage\n')

print("charset size:", len(charset))
print("total chars generated:", repeat_char * len(charset))
