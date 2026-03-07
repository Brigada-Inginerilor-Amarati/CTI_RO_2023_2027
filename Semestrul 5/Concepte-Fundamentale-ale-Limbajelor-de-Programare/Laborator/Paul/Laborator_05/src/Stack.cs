/*
3. Implementați o colecție generică Stack<T> folosind o List<T>. Colecția trebuie să aibă următoarele metode:
*/

public class Stack<T>
{
    public void Push(T t)
    {
        data.Add(t);
    }

    public T Pop()
    {
        if (data.Count == 0)
        {
            throw new Exception("Stiva este goala");
        }
        T t = data.Last();
        data.Remove(t);
        return t;
    }

    public bool TryPop(out T t)
    {
        if (data.Count == 0)
        {
            t = default(T);
            return false;
        }
        t = this.Pop();
        return true;
    }

    public T Peek()
    {
        if (data.Count == 0)
        {
            throw new Exception("Stiva este goala");
        }
        return data.Last();
    }

    private new string ToString()
    {
        return string.Join(", ", data);
    }

    List<T> data = new List<T>();

    public static void Main()
    {
        Stack<int> stack = new Stack<int>();
        stack.Push(1);
        stack.Push(2);
        stack.Push(3);
        Console.WriteLine("STACK: " + stack.ToString());

        stack.Pop();
        Console.WriteLine("AFTER POP: " + stack.ToString());

        int peek = stack.Peek();
        Console.WriteLine(peek);
        Console.WriteLine("AFTER PEEK: " + stack.ToString());

        bool tryPop = stack.TryPop(out int t);
        Console.WriteLine(tryPop);
        Console.WriteLine(t);
        Console.WriteLine("AFTER TRY POP: " + stack.ToString());

        bool tryPop2 = stack.TryPop(out int t2);
        Console.WriteLine(tryPop2);
        Console.WriteLine(t2);
        Console.WriteLine("AFTER TRY POP 2: " + stack.ToString());

        bool tryPop3 = stack.TryPop(out int t3);
        Console.WriteLine(tryPop3);
        Console.WriteLine(t3);

        Console.WriteLine("AFTER TRY POP 3: " + stack.ToString());
        bool tryPop4 = stack.TryPop(out int t4);
        Console.WriteLine(tryPop4);
        Console.WriteLine(t4);
    }
}
