<!-- Left side column. contains the logo and sidebar -->
<aside class="main-sidebar">

    <!-- sidebar: style can be found in sidebar.less -->
    <section class="sidebar">

        <!-- Sidebar Menu -->
        <ul class="sidebar-menu">
            

            <!-- Optionally, you can add icons to the links -->
            <li><i class='fa'></i> <span><font color="white" size="6"><center>{{ Auth::user()->name }}</center></font></span></li>
            <li class="active"><a href="{{ url('home') }}"><i class='fa fa-link'></i> <span>Home</span></a></li>
            
            @if(Entrust::hasRole('user'))
            <li><a href="{{ url('filmy') }}"><i class='fa fa-link'></i> <span>Filmy</span></a></li>
            <li class="treeview">
                <a href="#"><i class='fa fa-link'></i> <span>Program</span> <i class="fa fa-angle-left pull-right"></i></a>
                <ul class="treeview-menu">
                    <li><a href="{{ url('aupark') }}">Aupark</a></li>
                    <li><a href="{{ url('eurovea') }}">Eurovea</a></li>
                </ul>
            </li>

            <li><a href="{{ url('reserve') }}"><i class='fa fa-link'></i> <span>Moje rezervácie</span></a></li>
            @endif
            

            @if(Entrust::hasRole('salesman'))
            <li><a href="{{ url('aupark_p') }}"><i class='fa fa-link'></i> <span>Projekcie aupark</span></a></li>
            <li><a href="{{ url('eurovea_p') }}"><i class='fa fa-link'></i> <span>Projekcie eurovea</span></a></li>
            @endif

            @if(Entrust::hasRole('boss'))
            <li><a href="{{ url('add_salesman') }}"><i class='fa fa-link'></i> <span>Pridaj pokladníka</span></a></li>
            <li><a href="{{ url('show_sales') }}"><i class='fa fa-link'></i> <span>Tržby</span></a></li>
            @endif

            <li><a href="{{ url('/auth/logout') }}"><i class='fa fa-link'></i> <span>Odhlásiť sa</span></a></li>
        </ul><!-- /.sidebar-menu -->
    </section>
    <!-- /.sidebar -->
</aside>
