/*
3. Implementați o colecție generică Stack<T> folosind o List<T>. Colecția trebuie să aibă următoarele metode:

public class Stack
{
 public void Push(T); // adaugă un element în stivă
 public T Pop(); // elimină un element din stivă și aruncă o excepție dacă stiva este goală
 public bool TryPop(out T); // returnează true și elementul ca parametru out dacă operația de pop a fost reușită sau false dacă stiva este goală
 public T Peek(); // obține elementul de la vârful stivei fără a-l elimina
}

*/

namespace Exercitiu_03{
    public class Stack<T>{
        private List<T> data = new List<T>();

        public void Push(T item){
            data.Add(item);
        }

        public T Pop(){

            if(data.Count == 0){
                throw new Exception("Stack is empty");
            }

            T itemRemoved = data[data.Count - 1];
            data.RemoveAt(data.Count - 1);

            return itemRemoved;
        }

        public bool TryPop(out T item){
            if(data.Count == 0){
                item = default(T);
                return false;
            }

            item = Pop();

            return true;
        }

        public T Peek(){
            if(data.Count == 0){
                throw new Exception("Stack is empty");
            }

            return data[data.Count - 1];
        }
    }

    class Program{
        public static void Main(string[] args){
            Stack<int> stack = new Stack<int>();

            stack.Push(1);
            stack.Push(2);
            stack.Push(3);
            stack.Push(4);
            stack.Push(5);


            Console.WriteLine("Pop: " + stack.Pop());
            Console.WriteLine("Pop: " + stack.Pop());
             Console.WriteLine("Pop: " + stack.Pop());
              Console.WriteLine("Pop: " + stack.Pop());
               Console.WriteLine("Pop: " + stack.Pop());


            Console.WriteLine("Peek: " + stack.Peek());

            Console.WriteLine("TryPop: " + stack.TryPop(out int item));
            Console.WriteLine("Item: " + item);
        }
    }
}