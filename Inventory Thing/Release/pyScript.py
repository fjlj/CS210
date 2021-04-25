import re
import string

purchasedItems = {}

def loadFile(filePath):
    if not purchasedItems:
        inFile = open(filePath,"r")
        for line in inFile.readlines():
            iKey = line.strip().lower().capitalize()
            if iKey in purchasedItems.keys():
                purchasedItems[iKey] += 1
            else:
                purchasedItems[iKey] = 1
        inFile.close()

        outFile = open("frequency.dat","w")
        for item in purchasedItems:
            outFile.write("{}: {}\n".format(item.ljust(max([len(k) for k in purchasedItems.keys()])), purchasedItems[item]))
        outFile.close()


def PrintPurchasedItems(filePath):
    loadFile(filePath)
    for item in purchasedItems:
        print("{}: {}".format(item.ljust(max([len(k) for k in purchasedItems.keys()])), purchasedItems[item]))
    

def ItemLookup(item,filePath):
    loadFile(filePath)
    return (purchasedItems[item.lower().capitalize()] if item.lower().capitalize() in purchasedItems.keys() else 0)