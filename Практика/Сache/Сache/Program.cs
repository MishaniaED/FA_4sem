using System;
using System.Collections.Generic;
using System.Threading;

namespace Сache 
{
    class Cache<T>
    {
        public TimeSpan time;
        public int maxsize;
        Dictionary<string, Tuple<T, DateTime>> data;

        public Cache(TimeSpan time, int maxsize)
        {
            this.time = time;
            this.maxsize = maxsize;
            this.data = new Dictionary<string, Tuple<T, DateTime>>(this.maxsize);
        }

        public void Save(string key, T value) {
            foreach (string _key in data.Keys) // проверяем время существования
                if (DateTime.Now - data[_key].Item2 >= time) 
                    data.Remove(_key);

            if (data.ContainsKey(key))        // если данный ключ уже используется
                throw new ArgumentException($"This key = '{key}' is already there.");

            if (data.Count != maxsize)
            {
                if (data.ContainsKey(key)) // если данный ключ уже используется
                    throw new ArgumentException($"This key = '{key}' is already there.");
                data.Add(key, new Tuple<T, DateTime>(value, DateTime.Now));  // если > maxsize то заменить самую старую запись
            }
            else
            {
                string min = "";
                foreach (string _key in data.Keys)
                {
                    min = _key;
                    break;
                }

                foreach (string _key in data.Keys)
                    if (data[min].Item2 > data[_key].Item2)
                        min = _key;

                data.Remove(min);
                if (data.ContainsKey(key)) // если данный ключ уже используется
                    throw new ArgumentException($"This key = '{key}' is already there.");

                data.Add(key, new Tuple<T, DateTime>(value, DateTime.Now));
            }
        }
        public Tuple<T, DateTime> Get(string key) {
            foreach(string _key in data.Keys)
                if (DateTime.Now - data[_key].Item2 >= time)
                    data.Remove(_key);
            
            if (!data.ContainsKey(key)) // если данного ключа нет в базе
                throw new KeyNotFoundException($"This key = '{ key }' is not in the database!");
            else 
                return data[key]; 
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            int timout = 10;
            int maxsize = 2;
            Cache<int> cache = new Cache<int>(TimeSpan.FromSeconds(timout), maxsize);
            cache.Save("Mickhail", 12);
            cache.Save("Vasa Pupkin", 34);
            Console.WriteLine(cache.Get("Mickhail"));
            //Thread.Sleep(10000);
            //cache.Save("Mickhail", 12);
        }
    }
}
