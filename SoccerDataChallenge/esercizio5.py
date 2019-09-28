import json

MATCH_ID = 2576302
HOME_TEAM_ID = 3161
AWAY_TEAM_ID = 3159

with open("events.json", 'r') as f:
    events = json.load(f)

count = 0

for e in events:
    if(e['matchId'] == MATCH_ID and e['teamId'] == AWAY_TEAM_ID and e['eventName'] == 'Foul' and e['matchPeriod'] == '2H'):
        count += 1

f = open("esercizio5.csv", "w")
f.write("n_falli_subiti\n")
f.write(str(count) + "\n")
f.close()
