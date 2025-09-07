## Sum of absolute values
This is helpful, for instance, for the Manhattan distance trick.

This is easy to understand by testing different sign combinations:
$$|m| + |n| = \text{max}(|m + n|, |m - n|), \quad \forall m, n \in \mathbb{R}$$

## Triangle Inequality
- **For real numbers**: $|a+b|\le |a|+|b|$. General: $\big|\sum_i a_i\big|\le 
    \sum_i |a_i|$

* **For vectors**: $\|u+v\|\le \|u\|+\|v\|$.
  General: $\big\|\sum_i v_i\big\|\le \sum_i \|v_i\|$.

- **Weighted version**: For $t\in[0,1]$.
$$
\big\|\,t u+(1-t) v\,\big\|\ \le\ t\|u\|+(1-t)\|v\|.
$$

>----
> This is easy to prove by setting $x = tu$ and $y = (1-t)v$.
>
>---

Or with many terms: for $t_i\ge0,\ \sum t_i=1$,

  $$
  \Big\|\sum_i t_i v_i\Big\|\ \le\ \sum_i t_i \|v_i\|.
  $$

<!-- 
* **Cauchy–Schwarz**: $|\vec a\cdot\vec b|\le\|\vec a\|\,\|\vec b\|$ (equality iff $\vec a,\vec b$ are linearly dependent). -->

## Affine Functions
These allows us to directly prove the convexity of a function.

* **Affine function (of $x\in\mathbb R^n$)**:
  $f(x)=A x + b$ where $A$ is a matrix (or vector in 1D/2D) and $b$ is a constant vector.
    * **In 2D: $f(x,y)=ax+by+c$.**

* **Linear vs. affine**: linear has **no** constant term ($b=0$); affine is "linear + shift"
* **Affine combination of points**: $t x+(1-t) y$ with $t\in[0,1]$ (more generally $\sum t_i x_i$ with $t_i\ge0,\sum t_i=1$).
* **Key property**: affine functions preserve affine combinations (**helpful for convex proofs**):

  $$
  f\big(t x+(1-t) y\big)=t f(x)+(1-t) f(y).
  $$
* **Useful fact**: the composition "norm $\circ$ affine" is convex: if $h(z)=\|z\|$ and $g(x)=A x+b$, then $h(g(x))$ is convex.
* **Line/half-plane in 2D**: line $ax+by+c=0$ is affine; signed distance to this line is $\dfrac{ax+by+c}{\sqrt{a^2+b^2}}$, i.e. (constant)*(affine).


## Vector Notation (helpful for following sections)
- **Unit direction** (unit vector along $b$):  
  $\hat b=\dfrac{b}{\lVert b\rVert}$

## Dot product ($\mathbb{R}^n$)

* **Definition:** $a\cdot b=\sum_i a_i b_i$.
* **Properties:** commutative; bilinear (distributes over $+$, pulls out scalars).
* **Norm:** $\|a\|^2=a\cdot a$.
* **Angle/orthogonality:** $a\cdot b=\|a\|\|b\|\cos\theta$.
  $a\perp b \iff a\cdot b=0$.

#### Projection (onto a nonzero vector $b$)
$b\neq 0$. "Signed length" is positive if $a$ points with $b$, negative if against.

- **Scalar component** (signed length of $a$ along the axis of $b$):  
  $\operatorname{comp}_b(a)=a\cdot \hat b=\dfrac{a\cdot b}{\lVert b\rVert}=\lVert a\rVert\cos\theta$

- **Vector projection** (`lineProj`: $a$'s "shadow" on $\mathrm{span}(b)$; closest point on that line to $a$):
  $\operatorname{proj}_b(a)=\dfrac{a\cdot b}{b\cdot b}\,b=(a\cdot \hat b)\,\hat b$

- **Rejection** (part of $a$ perpendicular to $b$):  
  $\operatorname{rej}_b(a)=a-\operatorname{proj}_b(a)$, with $\operatorname{rej}_b(a)\perp b$

  Can also be computed using the vector projection with the perpendicular vector.

Check [../../codeforces/gym/105112_nwerc_23_24/J/J.cpp](../../codeforces/gym/105112_nwerc_23_24/J/J.cpp).

<!-- * **Projection scalar:** $t=\dfrac{(p-a)\cdot (b-a)}{\|b-a\|^2}$.
  Foot: $a+t(b-a)$. Use $t\in[0,1]$ for “on segment”.
* **Distance point-line/segment (uses cross below for 2D):** see cross section. -->

## Cross product

### In 2D

* **Definition (scalar):** $\text{cross}(a,b)=a_x b_y-a_y b_x$.
* **Orientation:** $\text{sgn}\big(\text{cross}(b-a,c-a)\big) \rightarrow$ left turn (+), right turn (−), collinear (0).
* **Area:**

  * Triangle $\Delta abc$: $\dfrac{|\text{cross}(b-a,c-a)|}{2}$.
  * Polygon (shoelace): $\dfrac{1}{2}\big|\sum_i \text{cross}(p_i,p_{i+1})\big|$.
<!-- * **Distance point-line:** $\dfrac{|\text{cross}(b-a,p-a)|}{\|b-a\|}$.
  Point-segment: same with $t$ clamped to $[0,1]$ from the dot-product formula above.
* **Collinearity + on-segment:**
  $\text{cross}(b-a,c-a)=0$ and $0\le (c-a)\cdot(b-a)\le \|b-a\|^2$. -->
* Lagrange’s identity:
  $|\vec a\times\vec b|^2=|\vec a|^2|\vec b|^2-(\vec a\cdot\vec b)^2$.

### In 3D

* **Definition:** $a\times b=(a_2b_3-a_3b_2,\ a_3b_1-a_1b_3,\ a_1b_2-a_2b_1)$.
* **Properties:** bilinear, anti-commutative $a\times b=-(b\times a)$, not associative.
* **Magnitude:** $\|a\times b\|=\|a\|\,\|b\|\,|\sin\theta|$ (area of parallelogram).
* **Perpendicularity:** $(a\times b)\cdot a=(a\times b)\cdot b=0$.



<!-- 
Not reviewed notes for cross and dot products

* **Parallelogram law:** $\|\vec a+\vec b\|^2+\|\vec a-\vec b\|^2=2\|\vec a\|^2+2\|\vec b\|^2$.
* **Polarization (recover the dot product from norms):**

  $$
  \vec a\cdot\vec b=\tfrac12\big(\|\vec a+\vec b\|^2-\|\vec a\|^2-\|\vec b\|^2\big)
  =\tfrac14\big(\|\vec a+\vec b\|^2-\|\vec a-\vec b\|^2\big).
  $$

**Geometric interpretations**

* $\vec a\cdot\vec b$ is the signed length of $\vec a$ in direction $\vec b$ times $\|\vec b\|$:
  $\ \vec a\cdot\vec b=\|\vec b\|\,\|\operatorname{proj}_{\vec b}\vec a\|$ (with sign via $\cos\theta$).
* $\|\vec a\|^2$ is the squared length; orthogonality gives the Pythagorean identity
  $\|\vec a+\vec b\|^2=\|\vec a\|^2+\|\vec b\|^2$ when $\vec a\perp\vec b$.

**Vector triple product (BAC–CAB rules)**

$$
\vec a\times(\vec b\times\vec c)=(\vec a\cdot\vec c)\,\vec b-(\vec a\cdot\vec b)\,\vec c,
$$

$$
(\vec a\times\vec b)\times\vec c=(\vec a\cdot\vec c)\,\vec b-(\vec b\cdot\vec c)\,\vec a.
$$

**Scalar triple product (mixed product)**

$$
\vec a\cdot(\vec b\times\vec c)
=\vec b\cdot(\vec c\times\vec a)
=\vec c\cdot(\vec a\times\vec b)
=\det[\vec a\ \vec b\ \vec c],
$$

distributive in each slot and giving the (signed) volume of the parallelepiped spanned by $\vec a,\vec b,\vec c$.
 -->
