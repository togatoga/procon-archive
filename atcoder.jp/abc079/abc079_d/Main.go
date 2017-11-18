package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

var H, W int

func main() {
	fsc := NewFastScanner()
	H, W := fsc.NextInt(), fsc.NextInt()
	costs := make([][]int, 11)
	for i := 0; i < 10; i++ {
		costs[i] = make([]int, 10)
	}
	for i := 0; i < 10; i++ {
		for j := 0; j < 10; j++ {
			costs[i][j] = fsc.NextInt()
		}
	}
	for k := 0; k < 10; k++ {
		for i := 0; i < 10; i++ {
			for j := 0; j < 10; j++ {
				costs[i][j] = IntMin(costs[i][j], costs[i][k]+costs[k][j])
			}
		}
	}
	result := 0
	for i := 0; i < H; i++ {
		for j := 0; j < W; j++ {
			val := fsc.NextInt()
			if val == -1 {
				continue
			} else {
				result += costs[val][1]
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
