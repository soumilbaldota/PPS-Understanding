Conversations
---

## Terms

- P players in total.

- each player has `B` items in their memory, each item is newsworthy, like *Novak won 21-19* which belongs to Subject *Tennis*. items can also belong to multiple subjects like *McD icecream machines don't work*, here the subjects are *McD* and *icecream*.

- in these `B` items, `floor(B/2)` items are about one subject, remaining `B-floor(B/2)` items are about another subject.

- each of those B items has a *importance score* in `[0,1]`.

- S subjects in total. example of a subject - *Tennis*

- L length of conversation is fixed beforehand.

- A Coversation is a list of items 

Every item belongs to a particular subject


## Probability of speaking
Here is how the probability is working.
At any turn, without any history,

- 1 person is willing to contribute - 100% probability
- 2 persons are willing to contribute - 50% probability
- 3 people - either - `[50(prev), 25, 25]` or `[100/3, 100/3, 100/3]` each
- 4 people - either - `[50(prev), 50/3, 50/3, 50/3]` or `[25, 25, 25, 25]` each

If they have previously spoken we take there history into account.

```python

history: Dict[PersonId, ContributedItems] = {}
if pause_count == 3:
    return

if current_people == 0:
    pause_count += 1
    return

if personLastSpoke not in current_people:
    p = 100 / len(current_people)

else:

    pre_contri_count = [len(history[person]) for person in current_people]

    min_contribution_count = min(pre_contri_count)

    people_we_can_choose = sum(
        1 for person in current_people if len(history[person]) == min_contribution_count
    )

    if people_we_can_choose == 1:
        p = 100
    else:
        p = 100 / (people_we_can_choose - 1)
```

> Note :- the personLastSpoke wants to speak again his probability is fixed at 0.5

## Coherence of a conversation

This is a tricky one just because of the wording.

every item `I` in a conversation, we look at the previous `3` and next `3` items.

This forms a context set C<sub>I</sub> = `(I-1, I+1, I-2, I+2, I-3, I+3)`, here the set may be smaller than `6` elements, as context set may stop before any pause, or context set for the `I=0`, `I=1`, `I=2` as the prev items are less than 3.

Since each item can belong to `[1,2]` subjects, there are a maximum of `12` possible subjects for a context set. 

We `increase` the coherence score when in there is `more than one` matching subject in context of current item.

We `decrease` the coherence score when there is `less than one` matching subject.

```python

    # note i am not taking into account non repetition here yet.

    convo = ['Novak won 21-19', "McD icecream machines don't work"]
    subjects = [['tennis'], ['McD','icecream']]

    for index, item in enumerate(convo):

        context_items = set()
        dirs = [-1,-2,-3,1,2,3]

        for dir in dirs:
            if index+dir >= 0 and index+dir < len(convo) and not is_pause(convo[index+dir]):
                context_items.push(index)

        context_subjects = [subjects[index] for ci in context_items]

        sub_i = subjects[index]
        count_sub = min([context_subjects.count(sub_i) for sub in subjects[index]])
        if count_sub > 1:
            coherence+=1
        elif count_sub < 1:
            coherence -= 1

```

*Optimization Note:  we don't need to check coherence for every item in the conversation as we when we have score more than 1 we know that both items are in context of each other, and the score will end up being increased by 2, as the match would be found for the same subject again.*


## Importance

This is an easy metric, just maintain a sum of importance.

```python
net_importance = 0

for item in convo:
    if not item.is_repeated():
        net_importance += item.importance

```

## Non repetition

Keep track of previously discussed items.

If item is repeated:

- `importance=0`
- Does not contribute to coherence score.


## Freshness

This is an easy metric, just maintain a list of last 5 subjects and check after every pause if the subject is novel.

```python
for index, item in enumerate(convo):
    novelty_count = 0

    if index > 0 and is_pause(item[index-1]):
        last_5_subjs = set()
        for prev in range(index-5, index):
            if prev>=0:
                last_5_subjs.add(**subjects[prev])
        for subj in subjects[index]:
            if subj not in last_5_subjs:
                novelty_count+=1
    
    if novelty_count > 1:
        net_score += 2
    elif novelty_count == 1:
        net_score += 1

```

## Nonmonotonousness


This is an easy metric, We can modify the freshness calculation to get monotonicity

```python

for index, item in enumerate(convo):
    monotonic_count = 0

    last_3_subjs = set()
    for prev in range(index-3, index):
        if prev>=0:
            last_3_subjs.add(**subjects[prev])

    for subj in subjects[index]:
        if subj in last_3_subjs:
            monotonic_count+=1
    
    if monotonic_count >= 1:
        net_score -= 1

```
