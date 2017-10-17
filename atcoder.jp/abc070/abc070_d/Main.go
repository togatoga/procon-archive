package main
 
import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)
 
const MAX_N = 100010
 
type key struct {
	a, b int
}
 
var edges [MAX_N][]int
var cost map[key]int
var N, Q, K int
var result map[key]int64
 
func dfs(pos, pre int, sum int64) {
	result[key{K, pos}] = sum
	result[key{pos, K}] = sum
	for _, next := range edges[pos] {
		if next == pre {
			continue
		}
		dfs(next, pos, sum+int64(cost[key{pos, next}]))
	}
 
}
func main() {
	fsc := NewFastScanner()
	N = fsc.NextInt()
	cost = make(map[key]int)
	result = make(map[key]int64)
	for i := 0; i < N-1; i++ {
		a, b, c := fsc.NextInt(), fsc.NextInt(), fsc.NextInt()
		a--
		b--
		edges[a] = append(edges[a], b)
		edges[b] = append(edges[b], a)
		cost[key{a, b}] = c
		cost[key{b, a}] = c
	}
	Q, K = fsc.NextInt(), fsc.NextInt()
	K--
	dfs(K, -1, 0)
	for i := 0; i < Q; i++ {
		a, b := fsc.NextInt(), fsc.NextInt()
		a--
		b--
		fmt.Println(result[key{a, K}] + result[key{K, b}])
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