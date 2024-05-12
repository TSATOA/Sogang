from display import display
import numpy as np
import math

### point_in_polygon_input.txt를 읽어온다 ###
with open("point_in_polygon_input.txt","r") as f:
    input_lines = f.readlines()
whole_points = input_lines
in_out_list = [[int(x.split(" ")[0]),int(x.split(" ")[1])] for x in whole_points]

for k in range(1,4) :
    ### 파일을 열고 input_lines에 파일 내용을 저장한다###
    with open("input{}.txt".format(k), "r") as f:
        input_lines = f.readlines()
    whole_points = input_lines

    ###input파일의 N개의 점들을 나누어 list를 만든다###
    x_list = [int(x.split(" ")[0]) for x in whole_points]
    y_list = [int(x.split(" ")[1]) for x in whole_points]
    li = []
    N = 0
    for i in range(len(x_list)): 
        li.append([x_list[i],y_list[i]])
        N=i
    N+=1

    ### y값이 가장 작은 점을 골라 point에 넣는다 ###
    li.sort(key=lambda x:(x[0], x[1]))
    tan = []
    point = [li[0]]
    li.remove(li[0])

    ### point[0]을 기준으로 polar angle이 작은 순으로 정렬한다 ###
    for i in range(N-1):
        if li[i][0]-point[0][0] == 0:
            tan.append(float("inf"))
        else:
            tan.append(math.atan((li[i][1]-point[0][1])/(li[i][0]-point[0][0])))

    tan_sort_idx = np.argsort(tan)
    li = [li[i] for i in tan_sort_idx]

    ### ccw 작업이 필요하다 ###
    def ccw(p1,p2,p3):
        return (p1[0]*p2[1]+p2[0]*p3[1]+p3[0]*p1[1]) - (p2[0]*p1[1]+p3[0]*p2[1]+p1[0]*p3[1])

    ### 점 구해준다 ###
    for i in li:
        while len(point) > 1 and ccw(point[-2],point[-1],i) <= 0:
            point.pop()
        point.append(i)

    ### 넓이 구해준다 ###
    area = 0
    for i in range(len(point)):
        if i == len(point) - 1:
            area += np.cross(point[i],point[0])
        else :
            area += np.cross(point[i],point[i+1])
    area = area/2

    ### output파일로 만든다 ###
    with open("김태곤_output{}.txt".format(k), "w") as f:
        f.write("{}\n".format(round(area,1)))
        for i in point:
            f.write("{} {}\n".format(i[0],i[1]))

    ### 이미지 만들어준다 ###
    display("./input{}.txt".format(k),"./김태곤_output{}.txt".format(k))
    
    ### 점이 왼쪽에 있는지 오른쪽에 있는지 판별하기 p3는 점, p1p2는 선###
    def lr(p1,p2,p3):
        if p1[1] < p2[1]:
            a = [p2[0]-p1[0],p2[1]-p1[1]]
            b = [p3[0]-p1[0],p3[1]-p1[1]]
        else:
            a = [p1[0]-p2[0],p1[1]-p2[1]]
            b = [p3[0]-p2[0],p3[1]-p2[1]] 
        if np.cross(a,b) > 0 :
            return True
        else:
            return False

    ### in_out 점 판별하기 ###
    TorF = []
    for x in in_out_list:
        cnt = 0
        detect_y = 0
        for i in range(len(point)):
            if i == len(point) - 1:
                if (point[i][1] > x[1] and x[1] > point[0][1]) or (point[i][1] < x[1] and x[1] < point[0][1]):
                    if lr(point[i],point[0],x):
                        cnt+=1
            else:
                if (point[i][1] > x[1] and x[1] > point[i+1][1]) or (point[i][1] < x[1] and x[1] < point[i+1][1]):
                    if lr(point[i],point[i+1],x):
                        cnt+=1
        if cnt %2 == 1:
            TorF.append("in")
        else:
            TorF.append("out")    
    
    ### output파일로 만든다 ###
    with open("김태곤_point_in_polygon_output{}.txt".format(k), "w") as f:
        for i in TorF:
            f.write("{}\n".format(i))

    