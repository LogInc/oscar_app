package com.log.oscar;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

public class Home extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_home);
		
		Button oscarHouse, modes;
		
		modes = (Button) findViewById(R.id.modes);
		oscarHouse = (Button) findViewById(R.id.oscarHouse);
		
		oscarHouse.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent OH = new Intent();
				startActivity(OH);
			}
		});
		
		modes.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent Modes = new Intent("com.log.oscar.MODES");
				startActivity(Modes);
			}
		});
	}
}
