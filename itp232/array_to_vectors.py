def flatten(in_list):
    from string import maketrans;tbl=maketrans("[]","{}");
    print(str([item for sublist in in_list for item in sublist]).translate(tbl))
    
def vec(in_list,rows):
    output=[[] for i in range(rows)]
    k=0
    for i in range(rows):
        for j in range(rows):
            output[i].append(in_list[k])
            k+=1
    return output
   
def make_vec(rows):
    from random import uniform;output=[[] for i in range(rows)]
    for i in range(rows):
        for j in range(rows):
            output[i].append(round(uniform(100,1000),3))
    return output
