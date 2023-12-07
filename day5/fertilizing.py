def mapVals(f):
    line = f.readline()
    v = []
    while True:
      line = f.readline()
      if len(line) < 2: break
      v.append([int(n) for n in line.split()])
      
    return v

def checkSeed(seed, rng, m, i):
  i = 0
  nmin = 0

  if i == len(m): return seed
  
  min = -1
  
  for r in m[i]:
    print(r)
    if seed >= r[1] and seed < (r[1] + r[2]) and (seed + rng) >= (r[1] + r[2]):
        nmin = checkSeed(r[0] + r[2], rng, m, i+1)
        print("1:", nmin)
        if (min < 0 or nmin < min):
            min = nmin
    elif seed >= r[1] and (seed + rng): 
        nmin = checkSeed(r[0] + (seed - r[1]), rng, m, i+1)
        print("2:", nmin)
        if (min < 0 or nmin < min):
            min = nmin
        
  print(min)
  return min


def main():
    m = []
    line = "blah"
    with open('input.txt', 'r') as f:
        while line:
            line = f.readline()
            if (len(line) < 2): 
              continue
            arr = line.split()
            if arr[0] == "seeds:":
                seeds = [int(n) for n in arr[1:len(arr)]]
            else:
                m.append(mapVals(f))
    
    f.close()
    
    min = -1
    
    # print(m)
    
    for i in range(0, len(seeds)-1, 2):
        nmin = checkSeed(seeds[i], seeds[i+1], m, 0)
        if min < 0 or nmin < min: 
            min = nmin
            
    print ("Min found: ", min) 

    
if __name__ == "__main__":
    main()