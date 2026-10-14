// Apply names from docs/functions.csv (column name, name_source=debug_string) to the Ghidra program
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.io.*;
public class ApplyNames extends GhidraScript {
  public void run() throws Exception {
    BufferedReader r = new BufferedReader(new FileReader(getScriptArgs()[0])); r.readLine();
    String l; int n=0;
    while ((l=r.readLine())!=null) {
      String[] c = l.split(",",-1);
      if (!c[3].equals("debug_string") && !c[3].equals("manual") && !c[3].equals("redriver2")) continue;
      Function f = getFunctionAt(toAddr(c[0]));
      if (f==null || f.getName().equals(c[2])) continue;
      String nm=c[2]; if (getGlobalFunctions(nm).size()>0) nm=nm+"_"+c[0];
      f.setName(nm, SourceType.USER_DEFINED); n++;
    }
    println("renamed="+n);
  }
}
