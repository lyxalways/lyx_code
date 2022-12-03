# 多项式乘法学习笔记

---

## 零、写在前面

- ~~多项式太难了！~~  

- 这篇东西是写给自己看的，完成进度随缘，不要催更.  

- 以下默认 $a_0$ 至 $a_{n-1}$ , $b_0$ 至 $b_{n-1}$ 分别表示 $f(x)$ , $g(x)$ 的 各项系数，$n$ 为 $2$ 的正整次幂.  

- 感谢 $\LaTeX$ 带来的美好公式排版!  

---

## 一、朴素方法  

- 首先表示出 $f(x)$ 和 $g(x)$ :  

- $f(x)=\sum\limits_{i=0}^{i<n}a_ix^i$

- $g(x)=\sum\limits_{i=0}^{i<n}b_ix^i$

- 所以很显然有：

- $f(x)g(x)=\sum\limits_{i=0}^{i<n} \sum\limits_{j=0}^{j<n}a_ib_jx^{i+j}$

- 时间复杂度 $\Theta(n^2)$ .  

---

## 二、点值表示法（暴力）

### 1、优秀的思维  

- 我们知道，用 $n$ 个点可以表示一个 $(n-1)$ 次多项式.  

- 而当我们有 $f(x)$ , $g(x)$ 在 $\{x_0,\dots,x_{n-1}\}$ 处的点值表示 $\{f(x_0),\dots,f(x_{n-1})\}$ , $\{g(x_0),\dots,g(x_{n-1})\}$ , 那么 $f(x)g(x)$ 的点值表示法就是： $\{f(x_0)g(x_0),\dots,f(x_{n-1})g(x_{n-1})\}$  

- 显然这一步是 $\Theta(n)$ 的.  

---

### 2、但是……  

- **怎么把系数表示法转化成点值表示法呢？**

- 暴力仍然是 $\Theta(n)$ (选点 $\Theta(n)$ , 求值 $\Theta(n)$ ).  

- **怎么把点值表示法转换成系数表示法呢？**  

- 高斯消元？ $\Theta(n^3)$ 的时间复杂度不是闹着玩的！  

- 拉格朗日插值？ 又一个蓝色的多项式板子，难写不说，时间复杂度依旧是 $\Theta(n^2)$ .  

- 综上所述，我们现在的想法依旧是 $\Theta(n^2)$ 的.

---

### 3、瓶颈在哪呢？  

- 两个转化太慢了！

- **还有什么条件没有用？**

- 我们的 $\{x_0,\dots,x_{n-1}\}$ 是随便选的！  

- 考虑选用特殊的 $x$ 值.  

- 于是就有接下来的故事.  

---

## 三、系数转点值 （FFT）  

### 1、前置知识：$n$ 次单位根

- 在复数意义下， $\sqrt[n]{1}$ 有 $n$ 个答案，统称为 $n$ 次单位根.  

- 我们记它们为 $\{\omega_{n}^{0},\dots,\omega_{n}^{n-1}\}$ .  

- 由欧拉公式可以 $\Theta(1)$ 得到它们的值：  

- $\omega_{n}^{k}=\cos\ k \frac{2\pi}{n}+i\sin k\frac{2\pi}{n}$  

- 而很显然，它们有如下性质：  

- $\omega_{n}^{m} = \omega_{nk}^{mk}$  

- $\omega_{n}^{k+{\frac{1}{2}n}} = -\omega_{n}^{k}$  

- $\omega_{n}^{0} = \omega_{n}^{n} = 1$  

---

### 2、朴素FFT思想

- 我们可以取 $\{x_0,\dots,x_{n-1}\}$ 为 $\{\omega_{n}^{0},\dots,\omega_{n}^{n-1}\}$ .  

- 那么就有：  

- $\begin{aligned}
  f(x) &= \sum\limits_{i=0}^{i<n}a_ix^i \\
     &= \sum\limits_{i=0}^{i<n/2}a_{2i}x^{2i}+ \sum\limits_{i=0}^{i<n/2}a_{2i+1}x^{2i+1}\\
     &= \sum\limits_{i=0}^{i<n/2}a_{2i}x^{2i}+ x\sum\limits_{i=0}^{i<n/2}a_{2i+1}x^{2i}.  
\end{aligned}$

- 令 $h(x) = \sum\limits_{i=0}^{i<n/2}a_{2i}x^i$ , $u(x) = \sum\limits_{i=0}^{i<n/2}a_{2i+1}x^i$ ,则有：  

- $\begin{aligned}
  f(x) &= h(x^2)+xu(x^2)\\
     &= h(\omega_{n}^{2k}) + \omega_{n}^{k}u(\omega_{n}^{2k})\\
     &= h(\omega_{n/2}^{k}) + \omega_{n}^{k}u(\omega_{n/2}^{k})\\
     &\text{(若}2k\text{大于}n\text{则对}n\text{取余）}  
\end{aligned}$

- 所以只要知道 $h(x)$ 和 $u(x)$ 的点值表示法，我们就能就能 $\Theta(n)$ 求出 $f(x)$ 的点值表示法！  

- 可以看到FFT用了分治的方法优化并解决了系数转点值的问题，那么它的时间复杂度怎么样呢？  

---

### 3、时间复杂度分析

- $h(x)$ , $u(x)$ 的规模都是 $f(x)$ 的一半，当 $x=0$ 时问题自动解决，可以列出时间复杂度方程：  

- $$T(n) = 2T(\frac{n}{2})+\Theta(n)$$  

- $$\therefore T(n) = \Theta(nlog{n})$$  

- 所以FFT的时间复杂度为 $\Theta(nlog{n})$ .  

---

### 4、朴素递归版代码实现(会TLE)

```cpp
void fast_fast_tle(int limit,complex *a,int type)
{
    if(limit==1) return ;//只有一个常数项
    complex a1[limit>>1],a2[limit>>1];
    for(int i=0;i<=limit;i+=2)//根据下标的奇偶性分类
        a1[i>>1]=a[i],a2[i>>1]=a[i+1];
    fast_fast_tle(limit>>1,a1,type);
    fast_fast_tle(limit>>1,a2,type);
    complex Wn=complex(cos(2.0*Pi/limit) , type*sin(2.0*Pi/limit)),w=complex(1,0);
    //Wn为单位根，w表示幂
    for(int i=0;i<(limit>>1);i++,w=w*Wn)//这里的w相当于公式中的k 
        a[i]=a1[i]+w*a2[i],
        a[i+(limit>>1)]=a1[i]-w*a2[i];//利用单位根的性质，O(1)得到另一部分 
}
```

- (这是板子题第一篇题解的代码)

- (所有递归FFT都会因为申请空间的巨大常数爆时长)

---

### 5、从递归到迭代

---

#### (一)蝴蝶变换

- 很容易可以想到同时处理 $f(\omega_{n}^{k})$ 和 $f(\omega_{n}^{k+{\frac{1}{2}n}})$ 的值.  

- 它们等于 $h(\omega_{n/2}^{k}) + \omega_{n}^{k}u(\omega_{n/2}^{k})$ 和 $h(\omega_{n/2}^{k}) - \omega_{n}^{k}u(\omega_{n/2}^{k})$ (这里用到了性质二).

- 发现了吗？两个数和 $h(\omega_{n/2}^{k})$ , $u(\omega_{n/2}^{k})$ 在数组中占相同位置！

- 所以我们只要定义两个临时变量即可处理！

- 不要临时数组，只要 $2$ 个临时变量，FFT带回家！

- 常数分分钟减少！

- 还有一个问题：如何对系数进行分组？这是从递归到迭代最后的难关.

---

#### (二)序列操作

- 观察这张序列分组变换的图片：

![][序列变换图]

- 我们发现：我们只需要先把原序列处理成最底层的顺序，就可以逐级合并了！

- 观察首尾序列的二进制表示：

```cpp
000 001 010 011 100 101 110 111
000 100 010 110 001 101 011 111
```

- 聪明的你是不是已经发现，它是二进制翻转！

- 接下来 $\Theta(n)$ 预处理出 $1$ 到 $n$ 的翻转序列(这段代码自己模拟一下就懂了):  

```cpp
for(int i = 0;i < l;i++){
    r[i] = r[i/2]/2;
    if(i % 2 ==1) r[i] += l / 2;
}
```

- 剩下的事就很简单了.  

- 迭代版FFT,大功告成！  

---

### 6.迭代版代码实现(对于复杂的代码，要会悟)

```cpp
void FFT (cp f[]){
    for(int i = 0;i < l;i++)
        if(i < r[i]) swap(f[i],f[r[i]]);
    for(int len = 2;len <= l;len *= 2){
        int hl = len / 2;
        cp w = cp(cos(2*PI/len),sin(2*PI/len));//当前的本原单位根
        for(int st = 0;st < l;st += len){
            cp w1 = cp(1,0);
            for(int nd = st;nd < st+hl;nd++){
                cp t1 = f[nd],t2 = w1 * f[nd+hl];
                f[nd] = t1 + t2,f[nd+hl] = t1 - t2;
                w1 = w1 * w;
                //这三行是蝴蝶变换重点
            }
        }
    }
}
```

- 放上[AC][AC记录]记录

---

## 四、点值转系数(IFFT)



[序列变换图]: https://cdn.luogu.com.cn/upload/image_hosting/qcadqwfg.png

[AC记录]: https://www.luogu.com.cn/record/93648016
