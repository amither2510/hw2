import random
import sys
import collections

commandStr = ["addClan", "addPlayer",
              "clanFight", "getMinClan"]

SUCCESS = "SUCCESS"
FAILURE = "FAILURE"
INVALID_INPUT = "INVALID_INPUT"

ClanID = dict()
playersID = dict()
ClanScore = collections.defaultdict(list)
playersClan = dict()
LosingClans = set()

Clans_count = 0;
players_count = 0;


def initline():
    global ClanID, Clans_count
    inLine = "init 2 0 1"
    outLine = "init done."
    ClanID[0] = {}
    ClanID[1] = {}
    Clans_count += 2
    return inLine, outLine


# addClan clanID
def addClan():
    global ClanID, Clans_count
    clanID = random.randint(-2, 8)
    inLine = "addClan %d" % (clanID)
    outLine = "addClan: "
    if clanID < 0:
        outLine += INVALID_INPUT
    elif clanID in ClanID.keys():
        outLine += FAILURE
    else:
        ClanID[clanID] = {}
        Clans_count += 1
        outLine += SUCCESS
    return inLine, outLine

# addPlayer playerID score clanID
def addPlayer():
    global playersID, ClanID, ClanScore, playersClan, players_count
    playerID = random.randint(-10, 1000)
    score = random.randint(-10, 1000)
    clanID = random.randint(-2, 8)
    inLine = "addPlayer %d %d %d" % (playerID, score, clanID)
    outLine = "addPlayer: "
    if playerID < 0 or clanID < 0 or score <0:
        outLine += INVALID_INPUT
    elif playerID in playersID.keys() or clanID not in ClanID.keys():
        outLine += FAILURE
    else:
        playersID[playerID] = playerID
        if clanID in ClanScore.keys():
            ClanScore[clanID].append(score)
        else:
            ClanScore[clanID] = [score]
        playersClan[playerID] = clanID
        ClanID[clanID][playerID] = (playersID[playerID], clanID)
        players_count += 1
        outLine += SUCCESS
    return inLine, outLine

# getMinClan
def getMinClan():
    global ClanID, LosingClans
    inLine = "getMinClan"
    outLine = "getMinClan: "
    for Clan_id in sorted(ClanID):
        if Clan_id not in LosingClans:
            outLine += SUCCESS + " %d" % Clan_id
            break			
    return inLine, outLine

def sum_n_strongest(Clan, num):
    sortedClan = sorted(Clan, reverse=True)
    topNum = sortedClan[:num]
    Sum = 0
    for element in topNum:
        Sum += element
    return Sum
	
# clanFight clan1 clan2 k1 k2
def clanFight():
    global ClanID, ClanScore, LosingClans
    clan1 = random.randint(-1, 8)
    clan2 = random.randint(-1, 8)
    k1 = random.randint(-1, 10)
    k2 = random.randint(-1, 10)
    inLine = "clanFight %d %d %d %d" % (clan1, clan2, k1, k2)
    outLine = "clanFight: "
    if k1 <= 0 or k2 <= 0 or clan1 < 0 or clan2 < 0:
        outLine += INVALID_INPUT
    elif clan1 not in ClanID.keys() or clan2 not in ClanID.keys() or clan1 == clan2 or len(ClanID[clan1]) < k1 or len(ClanID[clan2]) < k2:
        outLine += FAILURE
    elif clan1 in LosingClans or clan2 in LosingClans:
        outLine += FAILURE
    else:
        sum1 = sum_n_strongest(ClanScore[clan1], k1)
        sum2 = sum_n_strongest(ClanScore[clan2], k2)
        if sum1 == sum2:
            if clan1 < clan2:
                LosingClans.add(clan2)
            else:
                LosingClans.add(clan1)
        elif sum1 < sum2:
            LosingClans.add(clan1)
        else:
            LosingClans.add(clan2)
        outLine += SUCCESS
    return inLine, outLine
    
def main():
    if len(sys.argv) < 3:
        print("Usage %s <lines>" % sys.argv[0])
        exit(0)
    lines = int(sys.argv[1])
    infname = "%s.in" % sys.argv[2]
    outfname = "%s.out" % sys.argv[2]
    functions = [addClan, addPlayer,
                 getMinClan, clanFight]
    with open(infname, 'wb') as infhandler:
        with open(outfname, 'wb') as outfhandler:
            inLine, outLine = initline()
            infhandler.write(inLine + "\n")
            outfhandler.write(outLine + "\n")
            while lines > 0:
                f = random.randint(0, len(functions)-1)
                func = functions[f]
                inLine, outLine = func()
                if inLine is not "":
                    infhandler.write(inLine + "\n")
                    outfhandler.write(outLine + "\n")
                    lines -= 1
            infhandler.write("quit\n")
            outfhandler.write("quit done.\n")


main()
