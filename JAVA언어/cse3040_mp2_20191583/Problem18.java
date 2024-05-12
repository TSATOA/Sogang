package mp8;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;


class MyMap extends TreeMap<String, Double> {
	//serialVersionUID=1L은 warning제거를 위해 선언하였다(제거해도 실행 결과 동일)
	private static final long serialVersionUID = 1L;
	public String toString() {
		StringBuilder sb = new StringBuilder();
		Map<String,Double> map = new TreeMap<String,Double>();
		forEach((key,value)->map.put(key, value));
		
		List<Map.Entry<String, Double>> list = new LinkedList<>(map.entrySet());
		Collections.sort(list,new Comparator<Map.Entry<String,Double>>(){
			public int compare(Map.Entry<String, Double > o1,Map.Entry<String, Double> o2) {
				if(o1.getValue()>o2.getValue()) {
					return 1;
				}else if(o1.getValue()-o2.getValue()==0) {
					return 1;
				}else {
					return -1;
				}
			}
			
		});
		Map<String,Double> sor = new LinkedHashMap<>();
		for(Iterator<Map.Entry<String, Double>>it = list.iterator();it.hasNext();) {
			Map.Entry<String, Double> entry = it.next();
			sor.put(entry.getKey(), entry.getValue());
		}
		
        Set<Map.Entry<String,Double>> set = sor.entrySet();
        Iterator<Map.Entry<String,Double>> it = set.iterator();
		while(it.hasNext()) {
			Map.Entry<String,Double> e = (Map.Entry<String,Double>)it.next();
			sb.append(e.getKey() + " " + e.getValue() + "\n");
		}
		
        return sb.toString();
    }
}

class MapManager{
	
	static Map<String,Double> readData(String a){
		Map<String,Double> ma = new MyMap();
		BufferedReader br;
		String line;
		int idx;
		String Fru;
		double cost;
		try {
			br = new BufferedReader(new FileReader(a));
		}catch(FileNotFoundException e) {
			return null;
		}
		while(true) {
			try {
				line = br.readLine();
				if(line == null) break;
				idx = line.indexOf(" ");
				Fru = line.substring(0,idx);
				cost = Double.parseDouble(line.substring(idx+1));
				ma.put(Fru,cost);
			}catch(IOException e) {
				e.printStackTrace();
			}
		}
		try {
			br.close();
		}catch(IOException e) {
			e.printStackTrace();
		}	
		
		return ma;
	}
}

public class Problem18 {
	
	public static void main(String args[]) {
		Map<String, Double> map = MapManager.readData("input.txt");
		if(map == null) {
			System.out.println("Input file not found.");
			return;
		}
		System.out.println(map);
	}
}
