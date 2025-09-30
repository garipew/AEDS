import sys
import random

def generate_weight(n):
    # Non-uniform distribution: exponential with scale based on n
    return max(1, int(random.expovariate(1/(n))))

def generate_connected_graph(n, m):
    # First, output a spanning tree to ensure connectivity
    vertices = list(range(n))
    random.shuffle(vertices)
    for i in range(1, n):
        u = vertices[i-1]
        v = vertices[i]
        w = generate_weight(n)
        yield (u, v, w)

    # Track used edges in a set for O(1) checks
    used_edges = set()
    for i in range(1, n):
        u, v = vertices[i-1], vertices[i]
        if u > v:
            u, v = v, u
        used_edges.add((u, v))

    # Now add extra edges lazily until reaching m
    edges_needed = m - (n - 1)
    while edges_needed > 0:
        u = random.randint(0, n-1)
        v = random.randint(0, n-1)
        if u == v:
            continue
        if u > v:
            u, v = v, u
        if (u, v) in used_edges:
            continue
        used_edges.add((u, v))
        w = generate_weight(n)
        yield (u, v, w)
        edges_needed -= 1


def main():
    if len(sys.argv) == 2:
        n = int(sys.argv[1])
        m = random.randint(n-1, n*(n-1)//2)  # Adjust edges automatically
    elif len(sys.argv) >= 3:
        n = int(sys.argv[1])
        m = int(sys.argv[2])
    else:
        n = random.randint(5, 10)
        m = random.randint(n-1, n*(n-1)//2)

    if m < n-1 or m > n*(n-1)//2:
        print("Invalid number of edges for given vertices.")
        return

    print(f"{n} {m}")
    for u, v, w in generate_connected_graph(n, m):
        print(u, v, w)


if __name__ == "__main__":
    main()
