import sqlite3, time, sys, csv

if __name__ == "__main__":
    Ns = [10_000, 50_000, 100_000, 200_000]
    with open(sys.argv[1], 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(["rows","time_s"])
        for N in Ns:
            conn = sqlite3.connect(":memory:")
            c = conn.cursor()
            c.execute("CREATE TABLE A (id INTEGER, val TEXT);")
            c.execute("CREATE TABLE B (id INTEGER, val TEXT);")
            for i in range(N):
                c.execute("INSERT INTO A VALUES (?,?)", (i, str(i)))
                c.execute("INSERT INTO B VALUES (?,?)", (i, str(i)))
            conn.commit()

            t0 = time.time()
            c.execute("SELECT A.id, A.val, B.val FROM A JOIN B ON A.id=B.id;")
            c.fetchall()
            t1 = time.time()
            elapsed = t1 - t0

            w.writerow([N, f"{elapsed:.6f}"])
            print(f"{N},{elapsed:.6f}")
            conn.close()
