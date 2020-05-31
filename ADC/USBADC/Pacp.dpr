program Pacp;

uses
  Forms,
  Uacp in 'E:\Program Files\Borland\Delphi7\Projects\usb_prog\Uacp.pas' {FACP},
  UGraph in 'E:\Program Files\Borland\Delphi7\Projects\usb_prog\UGraph.pas' {FGraph},
  UnitACP in 'E:\Program Files\Borland\Delphi7\Projects\usb_prog\UnitACP.pas',
  u_mapmem in 'E:\Program Files\Borland\Delphi7\Projects\usb_prog\u_mapMem.pas',
  D2XXUnit in 'E:\Program Files\Borland\Delphi7\Projects\usb_prog\D2XXUnit.pas';

{$R *.RES}



begin
  Application.Initialize;
  ASSIGN(FPSW,'ACP_delphi.CFG');
  {$I-}
  Reset(FPSW);
  {$I+}
    if IOResult <> 0 then
  with FFPSW do
    begin
      Time2[1]:=0.9;
      Time2[2]:=0.9;Time2[3]:=0.9;
      MasY:=25;
      NumNul:=0;
      ACP.TypePreob:='Wilkinson';ACP.wchod1:=3;ACP.kanal1:=1024;ACP.interf1:=0;
      HorMas:=ACP.kanal1;
      IsHintWin:=true;zapolnen:=true;
      Marc[1]:=100;Marc[2]:=110;
      Ml[1]:=10; Ml[2]:=20;
      Mr[1]:=1000; Mr[2]:=1010;
      Xl:=15.0;Xr:=1005.0;Xlc:=15.0;Xrc:=1005.0;
      SADC[1]:=0;SADC[2]:=0;SADC[3]:=0;
      IsAll:=true;
      FuncNumber:=1;
      StartTime[1]:=36000.1;StartTime[2]:=36000.1;StartTime[3]:=36000.1;
      Reg_Sdvig:=0; Sel:=0; MemADC:=0; MemProg:=0;
      Grubo:=0; Tochno:=0;
      DNU:=0;
      MySpektr:='Spektr';
      IsPeriod:=false;
    end
  else
      begin
           Read(FPSW,FFPSW);
           Close(FPSW);
      end;
  FirstWind:=true;
  Application.ShowHint:=FFPSW.IsHintWin;
  Application.HelpFile := 'Acp.hlp';
  Application.CreateForm(TFACP, FACP);
  Application.Run;
        
end.
