package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
)

const (
	maxN = 51
)

var N, K int

type Points []Point

type Point struct {
	y, x int
}

func (p Points) Len() int {
	return len(p)
}
func (p Points) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}
func (p Points) Less(i, j int) bool {
	if p[i].x > p[j].x {
		return true
	}
	return p[i].y < p[j].y
}

var points Points

func main() {
	fsc := NewFastScanner()
	N, K = fsc.NextInt(), fsc.NextInt()
	X := make([]int, 0)
	Y := make([]int, 0)
	for i := 0; i < N; i++ {
		x, y := fsc.NextInt(), fsc.NextInt()
		points = append(points, Point{y: y, x: x})
		X = append(X, x)
		Y = append(Y, y)
	}
	sort.Sort(points)
	sort.Ints(X)
	sort.Ints(Y)
	// fmt.Println(points)
	var result int64
	result = 1 << 62
	for i := 0; i < N; i++ {
		for j := i + 1; j < N; j++ {
			for k := 0; k < N; k++ {
				for l := k + 1; l < N; l++ {
					lx := X[i]
					rx := X[j]

					by := Y[k]
					uy := Y[l]

					cnt := 0
					for m := 0; m < N; m++ {
						y, x := points[m].y, points[m].x
						if lx <= x && x <= rx && by <= y && y <= uy {
							cnt++
						}
					}

					if cnt >= K {
						result = Int64Min(result, int64(rx-lx)*int64(uy-by))
					}
				}
			}
		}
	}
	fmt.Println(result)
}

//template
type FastScanner struct {
	r   *bufio.Reader
	buf []byte
	p   int
}

func NewFastScanner() *FastScanner {
	rdr := bufio.NewReaderSize(os.Stdin, 1024)
	return &FastScanner{r: rdr}
}
func (s *FastScanner) Next() string {
	s.pre()
	start := s.p
	for ; s.p < len(s.buf); s.p++ {
		if s.buf[s.p] == ' ' {
			break
		}
	}
	result := string(s.buf[start:s.p])
	s.p++
	return result
}
func (s *FastScanner) NextLine() string {
	s.pre()
	start := s.p
	s.p = len(s.buf)
	return string(s.buf[start:])
}
func (s *FastScanner) NextInt() int {
	v, _ := strconv.Atoi(s.Next())
	return v
}
func (s *FastScanner) NextInt64() int64 {
	v, _ := strconv.ParseInt(s.Next(), 10, 64)
	return v
}

func (s *FastScanner) pre() {
	if s.p >= len(s.buf) {
		s.readLine()
		s.p = 0
	}
}
func (s *FastScanner) readLine() {
	s.buf = make([]byte, 0)
	for {
		l, p, e := s.r.ReadLine()
		if e != nil {
			panic(e)
		}
		s.buf = append(s.buf, l...)
		if !p {
			break
		}
	}
}

//Max,Min
func IntMax(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func Int64Max(a, b int64) int64 {
	if a < b {
		return b
	}
	return a
}
func Float64Max(a, b float64) float64 {
	if a < b {
		return b
	}
	return a
}

func IntMin(a, b int) int {
	if a > b {
		return b
	}
	return a
}

func Int64Min(a, b int64) int64 {
	if a > b {
		return b
	}
	return a
}
func Float64Min(a, b float64) float64 {
	if a > b {
		return b
	}
	return a
}

//Gcd
func IntGcd(a, b int) int {
	if a < b {
		b, a = a, b
	}
	if b == 0 {
		return a
	}
	return IntGcd(b, a%b)
}
func Int64Gcd(a, b int64) int64 {
	if a < b {
		b, a = a, b
	}
	if b == 0 {
		return a
	}
	return Int64Gcd(b, a%b)
}

func IntAbs(a int) int {
	if a < 0 {
		a *= -1
	}
	return a
}

func Int64Abs(a int64) int64 {
	if a < 0 {
		a *= -1
	}
	return a
}
