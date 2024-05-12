############# Write Your Library Here ###########
from collections import deque
from collections import defaultdict
from math import inf
import heapq
import itertools
################################################


def search(maze, func):
    return {
        "bfs": bfs,
        "dfs":dfs,
        "astar": astar,
        "astar_four_circles": astar_four_circles,
        "astar_many_circles": astar_many_circles
    }.get(func)(maze)


def bfs(maze):
    """
    [Problem 01] 제시된 stage1 맵 세 가지를 BFS Algorithm을 통해 최단 경로를 return하시오.
    """
    start_point=maze.startPoint()
    path=[]
    ####################### Write Your Code Here ################################

    queue = deque()
    queue.append(start_point)

    matrix = [[0]*maze.getDimensions()[1] for _ in range(maze.getDimensions()[0])]

    matrix[start_point[0]][start_point[1]] +=1

    while queue:
        x, y = queue.popleft()
        if maze.isObjective(x,y) :
            des_row=x
            des_col=y
            break
        for i in maze.neighborPoints(x,y):
            if matrix[i[0]][i[1]] == 0:
                matrix[i[0]][i[1]] = matrix[x][y]+1
                queue.append((i[0],i[1]))
            
    for i in range(matrix[des_row][des_col]-1,-1,-1):
        path.insert(0,[des_row,des_col])
        for j in maze.neighborPoints(des_row,des_col):
            if(matrix[des_row][des_col]-1==matrix[j[0]][j[1]]):
                des_row = j[0]
                des_col = j[1]
    
    return path




    ############################################################################


def dfs(maze):
    """
    [Problem 02] 제시된 stage1 맵 세 가지를 DFS Algorithm을 통해 최단 경로를 return하시오.
    """
    start_point = maze.startPoint()
    path = []
    ####################### Write Your Code Here ################################

    stack = [start_point]
    matrix = [[0]*maze.getDimensions()[1] for _ in range(maze.getDimensions()[0])]
    matrix[start_point[0]][start_point[1]] +=1

    while stack:
        x,y = stack.pop()
        if maze.isObjective(x,y) :
            des_row=x
            des_col=y
            break
        for i in maze.neighborPoints(x,y):
            if matrix[i[0]][i[1]] == 0:
                matrix[i[0]][i[1]] = matrix[x][y]+1
                stack.append((i[0],i[1]))
            


    for i in range(matrix[des_row][des_col]-1,-1,-1):
        path.insert(0,[des_row,des_col])
        for j in maze.neighborPoints(des_row,des_col):
            if(matrix[des_row][des_col]-1==matrix[j[0]][j[1]]):
                des_row = j[0]
                des_col = j[1]


    return path
    ############################################################################



def manhattan_dist(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


def astar(maze):
    """
    [Problem 03] 제시된 stage1 맵 세가지를 A* Algorithm을 통해 최단경로를 return하시오.
    (Heuristic Function은 위에서 정의한 manhattan_dist function을 사용할 것.)
    """
    start_point = maze.startPoint()
    path = []
    ####################### Write Your Code Here ################################
    
    opList = []
    clList = []
    cnt = 0
    opList.append([start_point,[0,0,0],None])
    for i in range(maze.getDimensions()[0]):
        for j in range(maze.getDimensions()[1]):
            if maze.isObjective(i,j):
                des_row = i
                des_col = j
    end = (des_row,des_col)


    while opList:
        cN = opList[0]
        for i in opList:
            if i[1][0]<cN[1][0]:
                cN = i
        opList.remove(cN)
        clList.append(cN)

        if cN[0] == end:
            N = cN
            while N:
                path.insert(0,N[0])
                N=N[2]
            return path
        
        for i in maze.neighborPoints(cN[0][0],cN[0][1]):
            Ne = [i,[0,0,0],cN]
            for j in clList:
                if Ne[0] == j[0]:
                    cnt=1
            if cnt == 1:
                cnt = 0
                continue
            Ne[1][1] = cN[1][1] + 1
            Ne[1][2] = manhattan_dist(i,end)
            Ne[1][0] = Ne[1][1]+Ne[1][2]

            for j in opList:
                if Ne[0]==j[0] and Ne[1][1]<j[1][1]:
                    opList.remove(j)
            opList.append(Ne)
            

    ############################################################################



def stage2_heuristic(p1,p2):
    dx = abs(p1[0] - p2[0])
    dy = abs(p1[1] - p2[1])
    return dx*dx + dy*dy


def astar_four_circles(maze):
    """
    [Problem 04] 제시된 stage2 맵 세 가지를 A* Algorithm을 통해 최단경로를 return하시오.
    (Heuristic Function은 직접 정의할것 )
    """
    start_point = maze.startPoint()
    path = []
    ####################### Write Your Code Here ################################

    dotc=[]  #조합
    dots=[]  #circle들
    ### dots에 circle들 저장
    for i in range(maze.getDimensions()[0]):
        for j in range(maze.getDimensions()[1]):
            if maze.isObjective(i,j):
                des_row = i
                des_col = j
                dots.append((i,j))

    ### dotc에 나올 수 있는 조합들 저장
    com = itertools.combinations(dots,2)
    for i in list(com):
        dotc.append(i)
    for i in dots:
        dotc.append((start_point,i))

    paths = []

    ### astar 알고리즘을 이용하여 paths에 조합에서 나올 수 있는 최단 길이들 저장
    for (first,end) in dotc:
        opList = []
        clList = []
        opList.append([first,[0,0,0],None])
        cnt = 0
        path=[]
        while opList:
            cN = opList[0]
            for i in opList:
                if i[1][0]<cN[1][0]:
                    cN = i
            opList.remove(cN)
            clList.append(cN)

            if cN[0] == end:
                N = cN
                while N:
                    path.insert(0,N[0])
                    N=N[2]
                paths.append(path)
                break
            
            for i in maze.neighborPoints(cN[0][0],cN[0][1]):
                Ne = [i,[0,0,0],cN]
                for j in clList:
                    if Ne[0] == j[0]:
                        cnt=1
                if cnt == 1:
                    cnt = 0
                    continue
                Ne[1][1] = cN[1][1] + 1
                Ne[1][2] = stage2_heuristic(i,end)
                Ne[1][0] = Ne[1][1]+Ne[1][2]

                for j in opList:
                    if Ne[0]==j[0] and Ne[1][1]<j[1][1]:
                        opList.remove(j)
                opList.append(Ne)

    ### dotp에 4점을 지나는 모든 경로 저장
    path=[]
    per = itertools.permutations(dots,4)
    dotp = []
    for i in list(per):
        dotp.append(i)



    findd = 0
    lens = inf

    ### dotp조합들 중 가장 길이가 짧은 조합 찾기
    for idx,i in enumerate(dotp):
        leni = 0
        d = (start_point,i[0])
        leni += len(paths[dotc.index(d)])
        for j in range(3):
            d=[]
            d = (i[j],i[j+1])
            if d in dotc:
                leni+=len(paths[dotc.index(d)])
            else:
                d = (i[j+1],i[j])
                leni+=len(paths[dotc.index(d)])
        if(lens>leni):
            lens = leni
            findd = idx
    
    ### 가장 짧은 조합 path에 추가
    d = (start_point,dotp[findd][0])
    for i in paths[dotc.index(d)]:
        path.append(i)

    for i in range(3):
        d = (dotp[findd][i],dotp[findd][i+1])
        if d in dotc:
            for j in paths[dotc.index(d)]:
                if j != paths[dotc.index(d)][0]:
                    path.append(j)
        else:
            d = (dotp[findd][i+1],dotp[findd][i])
            paths[dotc.index(d)].reverse()
            for j in paths[dotc.index(d)]:
                if j != paths[dotc.index(d)][0]:
                    path.append(j)
        
    return path
    

    ############################################################################








def mst(start,Vertex,Edge,comb):

    visited_set = set()
    visited_set.add(start)
    distance = 0
    min = inf
    n = len(Vertex)
    for i in range(n-1):
        min_dist = inf
        next_node = []
        for j in visited_set:
            for k in range(0,n):
                lens = -1
                if Vertex[k] not in visited_set:
                    if (j,Vertex[k]) in comb:
                        id = comb.index((j,Vertex[k]))
                    elif (Vertex[k],j) in comb:
                        id = comb.index((Vertex[k],j))

                    lens = len(Edge[id])
                    
                    if 0<lens<min_dist:
                        min_dist = len(Edge[id])
                        next_node = Vertex[k]
        distance += min_dist
        visited_set.add(next_node)
    return distance

    
    

def stage3_heuristic(start,Vertex,Edge,comb):
    return mst(start,Vertex,Edge,comb)
    


def astar_many_circles(maze):
    """
    [Problem 04] 제시된 stage3 맵 다섯 가지를 A* Algorithm을 통해 최단 경로를 return하시오.
    (Heuristic Function은 직접 정의 하고, minimum spanning tree를 활용하도록 한다.)
    """
    start_point = maze.startPoint()
    path = []
    ####################### Write Your Code Here ################################
    
    dotc=[]  #조합
    dots=[]  #circle들
    ### dots에 circle들 저장
    for i in range(maze.getDimensions()[0]):
        for j in range(maze.getDimensions()[1]):
            if maze.isObjective(i,j):
                des_row = i
                des_col = j
                dots.append((i,j))

    ### dotc에 나올 수 있는 조합들 저장
    com = itertools.combinations(dots,2)
    for i in list(com):
        dotc.append(i)
    for i in dots:
        dotc.append((start_point,i))

    pathss = []

    ### astar 알고리즘을 이용하여 pathss에 조합에서 나올 수 있는 최단 길이들 저장
    for (first,end) in dotc:
        opList = []
        clList = []
        opList.append([first,[0,0,0],None])
        cnt = 0
        paths=[]
        while opList:
            cN = opList[0]
            for i in opList:
                if i[1][0]<cN[1][0]:
                    cN = i
            opList.remove(cN)
            clList.append(cN)

            if cN[0] == end:
                N = cN
                while N:
                    paths.insert(0,N[0])
                    N=N[2]
                pathss.append(paths)
                break
            
            for i in maze.neighborPoints(cN[0][0],cN[0][1]):
                Ne = [i,[0,0,0],cN]
                for j in clList:
                    if Ne[0] == j[0]:
                        cnt=1
                if cnt == 1:
                    cnt = 0
                    continue
                Ne[1][1] = cN[1][1] + 1
                Ne[1][2] = stage2_heuristic(i,end)
                Ne[1][0] = Ne[1][1]+Ne[1][2]

                for j in opList:
                    if Ne[0]==j[0] and Ne[1][1]<j[1][1]:
                        opList.remove(j)
                opList.append(Ne)


    ### 다시 한번 A*알고리즘을 시행해준다.###
    path=[]
    opList = []
    clList = []
    cnt = 0
    dot = []
    c=0
    cn = 0
    cnn = 0
    paths = []
    opList.append([start_point,[0,0,0],None])
    dots=[]
    for i in range(maze.getDimensions()[0]):
        for j in range(maze.getDimensions()[1]):
            if maze.isObjective(i,j):
                des_row = i
                des_col = j
                dot.append((i,j))

    d = inf

    for i in dot:
        dots.append(i)
    
    
    ###점의 수만큼 실행해준다.###
    for z in range(len(dots)):
        de = dots[z]
        c = 0
        cn = 0
        cnn = 0
        opList = []
        clList = []
        opList.append([start_point,[0,0,0],None])
        path=[]
        dot = []
        for i in dots:
            dot.append(i)
        while opList:
            cN = opList[0]
            for i in opList:
                if i[1][0]<cN[1][0]:
                    cN = i
            opList.remove(cN)
            clList.append(cN)

            if cN[0] in dot:
                c+=1
                N = cN
                dot.remove(cN[0])

                if c!=0 and c!=len(dots):
                    N=N[2]
                while N:
                    path.insert(cn,N[0])
                    N=N[2]
                    cnn+=1
                ### Ne[1][2] (다음 이동 경로의 휴리스틱값) 을 구하기 위해 de가 필요하다###
                ### prim algorithm을 사용한 MST를 활용하여 최적의 목적지를 구하였다###
                cn = cnn
                d=inf
                for i in dot:
                    if d> stage2_heuristic(i,cN[0])+stage3_heuristic(i,dot,pathss,dotc):
                        d = stage2_heuristic(i,cN[0])+stage3_heuristic(i,dot,pathss,dotc)
                        de = i
    
                if c == len(dots):
                    paths.append(path)
                    break
                else:
                    opList = []
                    clList = []
                    clList.append([cN[0],[0,0,0],None])
                    cN = clList[0]

            for i in maze.neighborPoints(cN[0][0],cN[0][1]):
                Ne = [i,[0,0,0],cN]

                for j in clList:
                    if Ne[0] == j[0]:
                        cnt=1

                if cnt == 1:
                    cnt = 0
                    continue
                Ne[1][1] = cN[1][1] + 1
                Ne[1][2] = stage2_heuristic(i,de)
                Ne[1][0] = Ne[1][1]+Ne[1][2]

                for j in opList:
                    if Ne==j and Ne[1][1]<j[1][1]:
                        opList.remove(j)
                opList.append(Ne)


    path = paths[0]

    for i in paths:
        if len(path) > len(i):
            path = i

    return path

    


    ############################################################################
