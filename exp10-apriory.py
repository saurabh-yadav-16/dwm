def load_data():
    data = [
        ['milk', 'bread', 'nuts'],
        ['milk', 'bread', 'diapers', 'beer'],
        ['milk', 'bread', 'diapers'],
        ['bread', 'nuts', 'diapers', 'beer'],
        ['bread', 'nuts', 'diapers']
    ]
    return data

def create_candidates(transactions, itemset, length):
    candidates = []
    for i in range(len(itemset)):
        for j in range(i + 1, len(itemset)):
            candidate = list(set(itemset[i]) | set(itemset[j]))
            if len(candidate) == length:
                is_valid = True
                for item in candidate:
                    if item not in itemset[i] or item not in itemset[j]:
                        is_valid = False
                        break
                if is_valid:
                    candidates.append(candidate)
    return candidates

def apriori(transactions, min_support):
    itemset = [[item] for item in set(item for transaction in transactions for item in transaction)]
    frequent_itemsets = []
    length = 1

    while itemset:
        candidates = create_candidates(transactions, itemset, length)
        counts = [0] * len(candidates)

        for transaction in transactions:
            for i, candidate in enumerate(candidates):
                if all(item in transaction for item in candidate):
                    counts[i] += 1

        frequent_itemset = [candidates[i] for i in range(len(candidates)) if counts[i] >= min_support]

        frequent_itemsets.extend(frequent_itemset)

        itemset = frequent_itemset
        length += 1

    return frequent_itemsets

if __name__ == "__main__":
    transactions = load_data()
    min_support = 2
    frequent_itemsets = apriori(transactions, min_support)

    print("Frequent Itemsets with Min Support of", min_support, ":")
    for itemset in frequent_itemsets:
        print(itemset)
