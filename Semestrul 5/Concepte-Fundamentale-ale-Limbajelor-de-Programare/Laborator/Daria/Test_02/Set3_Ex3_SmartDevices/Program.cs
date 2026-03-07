using System;
using System.Collections.Generic;
using System.Threading.Tasks;

abstract class SmartDevice{
    public string Name { get; }
    public string Status { get; protected set; } 
    
    public SmartDevice(string name)
    {
        Name = name;
        Status = "Unknown";
    }

    public abstract void UpdateStatus();
}

class LightBulb : SmartDevice
{
    private static Random _rng = new Random();

    public LightBulb(string name) : base(name) { }

    public override void UpdateStatus()
    {
        bool working = _rng.Next(2) == 0;
        Status = working ? "On" : "Off";
        Console.WriteLine($"[LightBulb] {Name} status changed to: {Status}");
    }
}

class SmartPlug : SmartDevice
{
    private static Random _rng = new Random();

    public SmartPlug(string name) : base(name) { }

    public override void UpdateStatus()
    {
        bool connected = _rng.Next(2) == 0;
        Status = connected ? "Connected" : "Disconnected";
        Console.WriteLine($"[SmartPlug] {Name} status changed to: {Status}");
    }
}

class DeviceManager
{
    private List<SmartDevice> _devices = new List<SmartDevice>();

    public void AddDevice(SmartDevice device)
    {
        _devices.Add(device);
        Console.WriteLine($"Device added: {device.Name}");
    }

    public void RefreshAll()
    {
        Console.WriteLine("Refreshing all devices...");
        foreach (var device in _devices)
        {
            device.UpdateStatus();
        }
    }
}

class DeviceTimer
{
    public event Action Tick;
    private int _intervalMs;

    public DeviceTimer(int intervalMs)
    {
        _intervalMs = intervalMs;
    }

    public async Task StartAsync()
    {
        while (true)
        {
            await Task.Delay(_intervalMs);
            Tick?.Invoke();
        }
    }
}

class Program{
    static void Main(string[] args){
        MainAsync(args).GetAwaiter().GetResult();
    }

    static async Task MainAsync(string[] args)
    {
        DeviceManager manager = new DeviceManager();
        
        manager.AddDevice(new LightBulb("Bulb 1 (Living Room)"));
        manager.AddDevice(new LightBulb("Bulb 2 (Kitchen)"));
        manager.AddDevice(new SmartPlug("Plug 1 (TV)"));
        manager.AddDevice(new SmartPlug("Plug 2 (Fridge)"));

        // Abonare RefreshAll() la Tick si pornire timer.
        DeviceTimer timer = new DeviceTimer(2000); // 2 secunde

        timer.Tick += manager.RefreshAll;

        Console.WriteLine("Starting Timer (Ctrl+C to stop)...");
        await timer.StartAsync();
    }
}

