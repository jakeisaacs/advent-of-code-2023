totala = 0
totalb = 0
with open("input.txt") as file:
    input = file.readlines()
    for y in range(len(input)):
        for x in range(len(input[0])):
            gearcount = 0
            gearMult = 1
            print(y + "," + x)
            if not (input[y][x]).isdigit() and input[y][x] not in [".","\n"]:
                for yOFF in range(y-1,y+2):
                    for xOFF in ["-3,0","-2,1","-1,2","0,3","1,4","-2,0","-1,1","0,2","1,3","-1,0","0,1","1,2"]:
                        xa,xb=[int(a) for a in xOFF.split(",")]
                        if input[yOFF][x+xa:x+xb].isdigit():
                            gearcount+=1
                            number = int(input[yOFF][x+xa:x+xb])
                            totala += number
                            gearMult *= number
                            input[yOFF] = input[yOFF][0:x+xa] + ("." * abs(xa-xb)) + input[yOFF][x+xb:]
            if gearcount == 2:
                totalb += gearMult
print("answer 1 = ", totala)