int low=0,high=2505;
while(low+1<high){
    int mid=(low+high)/2;
    if(deci2(mid)) high=mid;
    else low=mid;
}
