package com.personal.testn9;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;

import com.personal.util.*;

public class TestN9Activity extends Activity implements View.OnClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test_n9);
        findViewById(R.id.btn_test_dlopen).setOnClickListener(this);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.test_n9, menu);
        return true;
    }


    @Override
    public void onClick(View v) {
        // TODO Auto-generated method stub
        int id = v.getId();
        if (id == R.id.btn_test_dlopen)
        {
            Native.testDlopen();
        }
        
    }
    
}
