
def mapVals(f):
    line = "blah"
    v = [[]]
    while(len(line) > 0):
        v.append([int(n) for n in line.split()])
        

def main():
    m = [[[]]]
    line = "blah"
    with open('input.txt', 'r') as f:
        while line:
            line = f.readline()
            arr = line.split()
            if arr[0] == "seeds:":
                seeds = arr[1:len(arr)]
                print(seeds)
            elif len(line) > 0:
                m.append(mapVals(f))
    
    f.close()
    
if __name__ == "__main__":
    main()