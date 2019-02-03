# bezier curver generator for practice. 

This generates a cubic Bezier curve. It can actually handle any order bezier curve. 

## Example Curve:
<p>For now the curve starts at (120,160) and ends at (220,40) Control points are (35,200), (220,260).</p>
<p>The Bezier curve is</p> 
<p>
{x = 120\*(1-t)^3 + 35\*3\*(1-t)^2 \* t + 220\*3\*(1-t)\*t^2 + 220\*t^3
</p>
<p>
{y = 160\*(1-t)^3 + 200\*3\*(1-t)^2 \* t + 260\*3\*(1-t)\*t^2 + 40\*t^3
</p>

Special thanks to pomax.github.io/bezierinfo
