using System;
using System.Collections.Generic;

namespace Laborator5
{
    class Program
    {
        public static void RemoveAt(int[] array, ref int length, int n)
        {
            if (n < 0 || n >= length)
                return;

            for (int i = n; i < length - 1; i++)
            {
                array[i] = array[i + 1];
            }

            length--;
        }

        public static List<int> Intersection(List<int> l1, List<int> l2)
        {
            List<int> result = new List<int>();
            List<int> seen = new List<int>();

            foreach (int item in l1)
            {
                if (l2.Contains(item) && !seen.Contains(item))
                {
                    result.Add(item);
                    seen.Add(item);
                }
            }

            return result;
        }
        
        
        public class Stack<T>
        {
            private List<T> items;

            public Stack()
            {
                items = new List<T>();
            }

            public void Push(T item)
            {
                items.Add(item);
            }

            public T Pop()
            {
                if (items.Count == 0)
                    throw new InvalidOperationException("Stack is empty");

                T item = items[items.Count - 1];
                items.RemoveAt(items.Count - 1);
                return item;
            }

            public bool TryPop(out T item)
            {
                if (items.Count == 0)
                {
                    item = default(T)!;
                    return false;
                }

                item = items[items.Count - 1];
                items.RemoveAt(items.Count - 1);
                return true;
            }

            public T Peek()
            {
                if (items.Count == 0)
                    throw new InvalidOperationException("Stack is empty");

                return items[items.Count - 1];
            }
        }

        static void Main()
        {
            Console.WriteLine("removeat:");
            int[] arr = { 1, 2, 3, 4, 5 };
            int len = 5;
            Console.Write("before: ");
            for (int i = 0; i < len; i++)
                Console.Write(arr[i] + " ");
            Console.WriteLine();
            
            RemoveAt(arr, ref len, 2);
            Console.Write("after - index 2: ");
            for (int i = 0; i < len; i++)
                Console.Write(arr[i] + " ");
            Console.WriteLine();
            
            RemoveAt(arr, ref len, 0);
            Console.Write("after - index0: ");
            for (int i = 0; i < len; i++)
                Console.Write(arr[i] + " ");
            Console.WriteLine();
            
            Console.WriteLine("\n intersection:");
            List<int> list1 = new List<int> { 1, 2, 3, 4, 5, 2 };
            List<int> list2 = new List<int> { 3, 4, 5, 6, 7, 3 };
            List<int> result = Intersection(list1, list2);
            Console.Write("list1: ");
            foreach (int x in list1)
                Console.Write(x + " ");
            Console.WriteLine();
            
            Console.Write("list2: ");
            foreach (int x in list2)
                Console.Write(x + " ");
            Console.WriteLine();
            
            Console.Write("intersection: ");
            foreach (int x in result)
                Console.Write(x + " ");
            Console.WriteLine();
            
            Console.WriteLine("\nstack:");
            Stack<int> stack = new Stack<int>();
            stack.Push(10);
            stack.Push(20);
            stack.Push(30);
            Console.WriteLine("pushed 10, 20, 30");
            Console.WriteLine("peek: " + stack.Peek());
            Console.WriteLine("pop: " + stack.Pop());
            Console.WriteLine("peek after pop: " + stack.Peek());
            
            bool success = stack.TryPop(out int value);
            Console.WriteLine("tryPop success: " + success + ", value: " + value);
            success = stack.TryPop(out value);
            Console.WriteLine("tryPop success: " + success + ", value: " + value);
            success = stack.TryPop(out value);
            Console.WriteLine("tryPop on empty stack: " + success);
            
            Stack<string> stringStack = new Stack<string>();
            stringStack.Push("hello");
            stringStack.Push("world");
            Console.WriteLine("string stack Peek: " + stringStack.Peek());
            Console.WriteLine("string stack Pop: " + stringStack.Pop());
        }
    }


}
