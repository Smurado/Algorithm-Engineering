# Topic

Monte-Carlo-Algorithm (Slide 21)

# Monte-Carlo-Algorithm

I wanted to research the origins of the name 'Monte Carlo algorithm' and explore its practical applications today.

## History

The core idea was conceived by mathematician Stanislaw Ulam while playing Solitaire. He realized it was much easier to estimate the probability of winning by simply playing the game 100 times and counting the wins, rather than trying to calculate it with complex mathematics. 

The name "Monte-Carlo" was then created by his colleague Nicholas Metropolis, referencing Ulam's uncle. His uncle would frequently borrow money from his relatives, claiming he needed to "go to Monte-Carlo" to gamble at the famous Monte Carlo Casino in Monaco. Because the new algorithm was fundamentally based on random chance and probability—much like casino games—the team adopted "Monte-Carlo" as the code name for their secret research during the Manhattan Project.

## Application in AlphaGo Zero

AlphaGo Zero uses Monte-Carlo Tree Search (MCTS) to master the complex game of Go. Instead of calculating every possible move, it simulates thousands of random games. By balancing the exploration of new moves with the exploitation of known winning strategies, it efficiently finds the optimal next move.

# Sources

- https://de.wikipedia.org/wiki/Monte-Carlo-Simulation#Geschichte
- https://jonathan-hui.medium.com/monte-carlo-tree-search-mcts-in-alphago-zero-8a403588276a