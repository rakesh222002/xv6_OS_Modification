import matplotlib.pyplot as pt
with open("./graph.txt") as target:
    given=map(lambda x: [int(x[0]),int(x[1]),int(x[2])],map(lambda x : x.split(" "),target.read().split("\n")))
points=list(given)
noofproc=25
noofproc=noofproc+4
startingindex=4
pt.yticks([0,1,2,3,4])
pt.xlabel("noofTicks")
pt.ylabel("QueueId")
for proc in range (startingindex,noofproc):
    px=[]
    py=[]
    for line in points:
        if(line[1]==proc):
            px.append(line[0])
            py.append(line[2])
    pt.plot(px,py, linestyle='--',marker='o',label=str(proc))
pt.legend()
pt.show()