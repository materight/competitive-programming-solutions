import json

MATCH_ID = 2576302
HOME_TEAM_ID = 3161
AWAY_TEAM_ID = 3159

with open("events.json", 'r') as f:
    events = json.load(f)


pass_count = {}
pass_max = {}
pass_count[HOME_TEAM_ID] = pass_count[AWAY_TEAM_ID] = 0
pass_max[HOME_TEAM_ID] = pass_max[AWAY_TEAM_ID] = 0

counting_team_id = -1

for e in events:
    if e['matchId'] == MATCH_ID:
        if e['eventName'] == 'Pass' and (counting_team_id == -1 or counting_team_id == e['teamId']) and any(tag['id'] == 1801 for tag in e['tags']):
            counting_team_id = e['teamId']
            pass_count[counting_team_id] += 1
        else:
            if pass_count[counting_team_id] > pass_max[counting_team_id]:
                pass_max[counting_team_id] = pass_count[counting_team_id]
            counting_team_id = e['teamId']
            pass_count[counting_team_id] = 1 if e['eventName'] == 'Pass' else 0

res = sorted(list(pass_max.items()), key=lambda x: x[0])

f = open("esercizio9.csv", "w")
f.write("teamId;n_pass_azione\n")
for teamId, count in res:
    f.write(str(teamId) + ";" + str(count) + '\n')
f.close()
