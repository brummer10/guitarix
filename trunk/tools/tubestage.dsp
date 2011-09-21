import("../src/faust/guitarix.lib");

tubestage_test(tb,fck,Rk,vplus,Vk0) = tube : hpf with {
    lpfk = lowpass1(fck);
    divider = 40;
    Rp = 100.0e3;
    VkC = Vk0 * (Rp/Rk);
    tube = (+ : -(Vk0) : Ftube(tb) : +(VkC-vplus)) ~ (*(Rk/Rp) : lpfk) : /(divider);
    hpf = _; //highpass1(31.0);
};

process = tubestage_test(tb,86.0,Rk,vplus,Vk0) with {
    tb = vslider("tb",0,0,9,1);
    Rk = vslider("Rk",2700,0,10000,0.01);
    Vk0 = vslider("Vk0", 0, -5, 5, 0.01);
    vplus = vslider("vplus", 250.0, 10, 400, 0.01);
};
