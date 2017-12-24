package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
)

var N, Q int

const (
	maxN = 100100
)

var sum1 [maxN]int64
var sum2 [maxN]int64

func main() {
	fsc := NewFastScanner()
	N, Q = fsc.NextInt(), fsc.NextInt()
	X := fsc.NextIntArray()
	T := []int{}
	S := []int{}
	for i := 0; i < Q; i++ {
		T = append(T, fsc.NextInt())

	}
	S = append(S, T...)
	sort.Ints(T)
	sum1[0] = 0

	for i := 1; i < N; i++ {
		sum1[i] += sum1[i-1]
		a := int64(i)
		sum1[i] += a * int64(X[i]-X[i-1])
	}
	sum2[N-1] = 0
	for i := N - 2; i >= 0; i-- {
		sum2[i] += sum2[i+1]
		a := int64(N - 1 - i)
		sum2[i] += a * int64(X[i+1]-X[i])
	}
	back := 0

	X = append(X, 1145141919810)
	var result int64
	dic := map[int]int64{}
	for i := 0; i < Q; i++ {
		result = 0
		for T[i] >= X[back] {
			back++
		}
		a := back - 1
		b := back
		// fmt.Println(a, b, i)
		if a >= 0 {
			result += sum1[a]
			diff1 := T[i] - X[a]
			result += int64(diff1) * int64((a + 1))
		}
		if b < N {
			result += sum2[b]
			diff2 := X[b] - T[i]
			result += int64(diff2) * int64((N - b))
		}
		dic[T[i]] = result
	}
	for i := 0; i < Q; i++ {

		fmt.Println(dic[S[i]])
	}
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

func (s *FastScanner) NextIntArray() []int {
	s.pre()
	start := s.p
	result := []int{}
	for ; s.p < len(s.buf)+1; s.p++ {
		if s.p == len(s.buf) || s.buf[s.p] == ' ' {
			v, _ := strconv.ParseInt(string(s.buf[start:s.p]), 10, 0)
			result = append(result, int(v))
			start = s.p + 1
		}
	}

	return result
}

func (s *FastScanner) NextInt64Array() []int64 {
	s.pre()
	start := s.p
	result := []int64{}
	for ; s.p < len(s.buf)+1; s.p++ {
		if s.p == len(s.buf) || s.buf[s.p] == ' ' {
			v, _ := strconv.ParseInt(string(s.buf[start:s.p]), 10, 64)
			result = append(result, v)
			start = s.p + 1
		}
	}
	return result
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
