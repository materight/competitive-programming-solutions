import json

MATCH_ID = 2576302
HOME_TEAM_ID = 3161
AWAY_TEAM_ID = 3159

with open("events.json", 'r') as f:
    events = json.load(f)


dist_x_sum = 0
dist_y_sum = 0
count = 0

for e in events:
    if e['matchId'] == MATCH_ID and e['subEventName'] == 'Ground defending duel' and e['teamId'] == AWAY_TEAM_ID:
        dist_x_sum += e['positions'][0]['x']
        dist_y_sum += e['positions'][0]['y']
        count += 1

res_x = round(dist_x_sum / count, 4)
res_y = round(dist_y_sum / count, 4)
f = open("esercizio11.csv", "w")
f.write("p_tackle_x;p_tackle_y\n")
f.write(str(res_x) + ';' + str(res_y) + '\n')
f.close()
