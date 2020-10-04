import os

if os.getcwd().replace('\\', '/').endswith("/scripts") or os.getcwd().replace('\\', '/').endswith("/scripts/"):
    os.chdir("..")

obj = []

for root, subdirs, files in os.walk("./obj"):
    for f in files:
        if f.endswith(".o"):
            obj.append(root.replace('\\', '/') + '/' + f)

f = open("./scripts/linker.ld", 'r')
linkerStr = f.read()
f.close()

f = open("./scripts/linker.ld.bak", 'w')
f.write(linkerStr)
f.close()

linkerArr = []

split_1 = linkerStr.split(sep="INPUT")

linkerArr.append(split_1[0])

split_2 = split_1[1].split(sep="OUTPUT")

linkerArr.append("OUTPUT" + split_2[0 if len(split_2) == 1 else 1])

linkerInput = "INPUT (\n"

for file in obj:
    linkerInput += ' '*4 + file + "\n"

linkerInput += ")\n\n"

linker = linkerInput.join(linkerArr)

f = open("./scripts/linker.ld", 'w')
f.write(linker)
f.close()
