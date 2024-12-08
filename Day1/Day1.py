from collections import defaultdict
def sortedLists(filepath):
    try:
        file = open(filepath, 'r')
    except FileNotFoundError:
        return "FileNotFound"
    else:
        list1 = []
        list2 = []
        lines = file.readlines()
        for line in lines:
            
            if not line:
                continue
                
            list1.append(int(line[:line.find(',')]))
            list2.append(int(line[line.find(',')+1:].strip()))


        list1 = sorted(list1)
        list2 = sorted(list2)
    return list1, list2

def distance_between_lists(list1, list2):
    length = len(list1)
    distance = []
    for i in range(length):
        distance.append(abs(list1[i] - list2[i]))

    result = sum(distance)
    print(result)
    
def similarity(left_List, right_List):
    right_counter = dict.fromkeys(left_List,0)
    left_counter = dict.fromkeys(left_List,0)

    for i in left_List:
        if i in left_counter:
            left_counter[i] += 1
        else:
            continue

    for j in right_List:
        if j in right_counter:
            right_counter[j] += 1
        else:
            continue

            
    similarities_score = []
    for key,value in right_counter.items():
        if key in left_counter:
            similarities_score.append((int(key) * int(value))*left_counter.get(key))

    result = sum(similarities_score)
    print(result)
    
    



def main():
    Testlist1, Testlist2 = sortedLists("Day1TestInput.csv")
    list1, list2 = sortedLists("Day1Input.csv")

    distance_between_lists(Testlist1, Testlist2)
    distance_between_lists(list1, list2)

    similarity(Testlist1, Testlist2)
    similarity(list1,list2)

main()