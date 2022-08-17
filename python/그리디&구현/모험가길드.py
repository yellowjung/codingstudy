n = int(input())
data = list(map(int, input().split()))
data.sort()

result = 0 # 총 그룹의 수
count = 0 # 현재 그룹에 포함된 모험가의 수

for i in data: # 공포도 낮은 것부터 하나씩
    count += 1 # 현재 그룹에 포함된 사람 증가
    if count >= i: # 공포도보다 사람 수가 많으면 그룹 만들기
        result += 1
        count = 0

print(result)