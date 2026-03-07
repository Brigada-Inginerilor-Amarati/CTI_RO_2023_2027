// 1. Scrieti un program care citeste n numere si afiseaza suma acestora.
using System;

class Task1 {
	public static void Main(){
		Console.WriteLine("Introduceti numarul de numere:");
		int n = Convert.ToInt32(Console.ReadLine());

		Console.WriteLine("Introduceti numerele:");
		int[] arr = new int[n];
		for(int i = 0; i < n; i++){
			arr[i] = Convert.ToInt32(Console.ReadLine());
		}

		int sum = 0;
		for(int i = 0; i < arr.Length; i++)
			sum += arr[i];

		Console.WriteLine("Suma numerelor este: " + sum);
	}
}
