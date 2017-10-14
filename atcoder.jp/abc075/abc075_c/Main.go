package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

const (
	maxN = 50
)

var edges [maxN][]int
var visited [maxN]bool

func dfs(pos int, a, b int) {
	visited[pos] = true
	for _, nxt := range edges[pos] {
		if visited[nxt] {
			continue
		}
		if pos == a && nxt == b {
			continue
		}
		dfs(nxt, a, b)
	}
}

func clear() {
	for i := 0; i < maxN; i++ {
		visited[i] = false
	}
}
func check() int {
	res := 0
	for i := 0; i < maxN; i++ {
		if visited[i] {
			res++
		}
	}
	return res
}
func main() {
	fsc := NewFastScanner()
	N, M := fsc.NextInt(), fsc.NextInt()
	for i := 0; i < M; i++ {
		a, b := fsc.NextInt(), fsc.NextInt()
		a--
		b--
		edges[a] = append(edges[a], b)
		edges[b] = append(edges[b], a)
	}
	result := 0
	for a := 0; a < N; a++ {
		for _, b := range edges[a] {
			clear()
			dfs(0, a, b)
			res := check()
			if res != N {
				result++
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
