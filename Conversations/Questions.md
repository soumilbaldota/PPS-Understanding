Coherence
---

Questions to ask in class:

1. Does a pause empty the context set ?
2. is the conversation realtime ? if the conversation "game" is running in realtime, how do we know what the next 3 items are going to be ?
3. Is the simulator going to give us updates after everytime regarding coherence score or at the end of the conversation?


Non repetition
---

1. When we say "does not contribute to coherence score", do we consider it both in negative and positive cases, where say we have 7 copies of the same item `["i1", "i1", "i1", "i1", "i1", "i1", "i1" ]` and obviously they have the same subjects so for the first instance of `i1`, and the context set has the same subjects for the first index so coherence goes up by 1. Then in the second instance,

 - do we ignore it because it is a repeating item ?
 - or do we reduce the coherence score by 1 as we ignore the subjects of all repeating items and the ?


Programming the player
---
When programming a player, what inputs do we get from the simulator?