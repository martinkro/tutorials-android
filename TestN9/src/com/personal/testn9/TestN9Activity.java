package com.personal.testn9;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class TestN9Activity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test_n9);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.test_n9, menu);
        return true;
    }
    
}
