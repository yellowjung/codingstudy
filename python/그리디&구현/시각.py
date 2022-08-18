h = int(input())

count = 0
for i in range(h + 1):
    for j in range(60):
        for k in range(60):
            #매 시각 안에 3이 포함되면 증가
            if '3' in str(i) + str(j) + str(k):
                count += 1
                
print(count)