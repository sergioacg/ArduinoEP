function [TK,TC] = T_ss(eps,sigma,A,U,Qi,Ta,alpha)
%Equilibrio
    p=[eps*sigma*A 0 0 U*A -alpha*Qi-U*A*Ta-eps*sigma*A*Ta^4];
    rp=roots(p);
    Ts=[];
    for i=1:4
        if isreal(rp(i)) && rp(i)>0
            Ts=[Ts;rp(i)];
        end
    end
  TK=Ts;
  TC=TK-273.15;