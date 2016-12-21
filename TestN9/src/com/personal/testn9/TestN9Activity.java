package com.personal.testn9;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.security.MessageDigest;
import java.util.UUID;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.TextView;

import com.personal.util.*;

public class TestN9Activity extends Activity implements View.OnClickListener{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Native.testHello();
        setContentView(R.layout.activity_test_n9);
        findViewById(R.id.btn_test_dlopen).setOnClickListener(this);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.test_n9, menu);
        return true;
    }
    
    public static String hexEncoded(byte[] data){
        char hex[] = {'0','1','2','3','4','5','6','7','8','9', 'A','B','C','D','E','F'};
        char result[] = new char[data.length * 2];
        int index = 0;
        for(byte b: data){
            result[index++] = hex[(b >>> 4) & 0x0F];
            result[index++] = hex[b & 0x0F];
        }
        return new String(result);
    }
    
    private String getUUID2(){
        String uuid = "00000";
        String key = "MTP_UUID_MD5";
        SharedPreferences sharedPref = getPreferences(Context.MODE_PRIVATE);
        uuid = sharedPref.getString(key, "000000");
        if (uuid.equals("000000"))
        {
            uuid = UUID.randomUUID().toString();
            try{
                MessageDigest md = MessageDigest.getInstance("MD5");
                byte[] md5 = md.digest(uuid.getBytes());
                uuid = hexEncoded(md5);
            }catch(Exception e)
            {
                
            }
           
            SharedPreferences.Editor editor = sharedPref.edit();
            editor.putString(key, uuid);
            editor.commit();
        }
        return uuid;
    }
    private String getUUID()
    {
        String uuid = "000000";
        boolean readSuccess = false;
        File fileUUID = new File(getFilesDir(), "mtp_uuid.dat");
        if (fileUUID.exists()){
            try{
                BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(fileUUID)));
                String line = reader.readLine();
                int pos = line.indexOf("uuid=");
                if (pos >= 0)
                {
                    uuid = line.substring(pos+5);
                    readSuccess = true;
                }
                
                reader.close();
                
            }
            catch(Exception e){
                
            }
            
            if (!readSuccess){
                fileUUID.delete();
            }
            
        }
        
        if(!readSuccess || (uuid.equals("000000")))
        {
            uuid = UUID.randomUUID().toString();
            FileOutputStream out = null;
            try {
                out = new FileOutputStream(fileUUID);
                String item = String.format("uuid=%s", uuid);
                out.write(item.getBytes());
                out.flush();
                out.close();
            } catch (FileNotFoundException e) {
            } catch (IOException e) {
            }
        }
        return uuid;
    }


    @Override
    public void onClick(View v) {
        // TODO Auto-generated method stub
        int id = v.getId();
        if (id == R.id.btn_test_dlopen)
        {
            Native.testDlopen();
            String uuid = MyApplication.getInstance().getUUID();
            TextView tv = (TextView)findViewById(R.id.tv_uuid);
            tv.setText(uuid);
            Log.d("testn9", "UUID:" + uuid);
        }
        
    }
    
}
