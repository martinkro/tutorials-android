package com.personal.util;

public class Native {

    static{
        
        System.loadLibrary("TestN9");
        System.loadLibrary("mono");
    }
    
    public static native void testDlopen();
    public static native void testHello();
}
