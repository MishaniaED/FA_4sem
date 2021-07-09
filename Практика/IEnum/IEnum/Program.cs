using System;
using System.Collections.Generic;
using System.Linq;

namespace IEnum
{
    public static class EnumerableExtentions
    {
        public static void FindRepeates(this IEnumerable<int> array, in IEqualityComparer<int> comp)
        {
            var unique_str_array = array.Distinct(comp);
            if (unique_str_array == array)
                throw new ArgumentException("Repeatables were found");
        }

        /* public static IEnumerable<IEnumerable<int>> GenCombinations(this IEnumerable<int> array, int k, in IEqualityComparer<int> comp) // генерация сочетаний
         {
             FindRepeates(array, in comp);
             return;
         }

        public static IEnumerable<IEnumerable<int>> GetSubsetsList(this IEnumerable<int> array, in IEqualityComparer<int> comp) // генерация подмнож
        {
            FindRepeates(array, in comp);
            List<IEnumerable<int>> subsets = new List<IEnumerable<int>>();
            List<int> set = array.ToList();

            return;
        }*/

        public static IEnumerable<IEnumerable<int>> GenPermutations(this IEnumerable<int> array, in IEqualityComparer<int> comp) // генерация возможных перестановок
        {
            FindRepeates(array, in comp);

            List<int> set = array.ToList();
            return Permute(set);
        }
    

        private static List<int[]> Permute(List<int> set)
        {
            List<int[]> result = new List<int[]>();

            Action<int> permute = null;
            permute = start =>
            {
                if (start == set.Count)
                {
                    result.Add(set.ToArray());
                }
                else
                {
                    List<int> swaps = new List<int>();
                    for (int i = start; i < set.Count; i++)
                    {
                        if (swaps.Contains(set[i])) continue; // skip if we already done swap with this item
                        swaps.Add(set[i]);

                        Swap(ref set, start, i);
                        permute(start + 1);
                        Swap(ref set, start, i);
                    }
                }
            };

            permute(0);

            return result;
        }


        private static void Swap(ref List<int> array, int i, int j)
        {
            if (array[i] == array[j])
                return;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    class Program
    {
        public class Equality : IEqualityComparer<int>
        {
            public bool Equals(int a, int b)
            {
                if (a == null || b == null)
                    return false;
                return (a == b);
            }
            public int GetHashCode(int str)
            {
                return str.GetHashCode();
            }
        }

        public static void Print(in IEnumerable<IEnumerable<int>> arr, string text)
        {
            Console.WriteLine(text);
            foreach (var obj in arr)
                foreach (var str in obj)
                    Console.Write(str + ' ');
            Console.WriteLine();
        }

        static void Main(string[] args)
        {
            IEqualityComparer<int> comp = new Equality();

            IEnumerable<IEnumerable<int>> objects_first = new List<List<int>>();

            List<int> data = new List<int>(new int[] { 1, 2, 3 });
            objects_first = data.GenPermutations(in comp);
            Print(in objects_first, "Permutations:");
        }
    }
}
