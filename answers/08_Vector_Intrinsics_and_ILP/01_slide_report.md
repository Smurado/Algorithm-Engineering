# Topic

Select one slide from the lecture, research more about the topic, and report on it.

## Selected topic

Page 3, "Fused-Multiply-Add (FMA)"

## Research

One of the slides contains Fused-Multiply-Add. As I didn't really get why this is explicitly mentioned, I researched it further.

### Why is it used?

Normally, an operation like `a + (b * c)` would be rounded after the multiplication. After this, the addition would be calculated, and it would be rounded again. This may be sufficient for most tasks, but it could be too imprecise and slow for others.

The solution to this is to have a separate unit in the processor with an extra-large internal 'memory' specifically designed for this kind of operation. The FMA unit will calculate the product and the addition immediately, and only after that will it round the final result down to fit into the standard float/double size (e.g., 64-bit). 

This approach is both faster and more precise.

### Example when it's used: AI

One very recent use case of this kind of operation is in AI, more specifically in neural networks.
Here, this kind of operation is the driving factor of the network computations.
The core operation inside such a network is shown below:

$$y = f(\sum (w \cdot x) + b)$$

* $x$: The input (e.g., an image pixel or part of a word). 
* $w$: The weight. How important is this input?
* $b$: The bias (a kind of base activation).