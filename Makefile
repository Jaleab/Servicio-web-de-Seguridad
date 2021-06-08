app: codigo/agregarItem.cpp codigo/articulo.cpp codigo/carritoCompra.cpp codigo/carritoCompraEmbed.cpp codigo/Checker.cpp codigo/ConectorModular.cpp codigo/conector.cpp codigo/finalizarCompra.cpp codigo/formularioArticulo.cpp codigo/formularioContacto.cpp codigo/framework.cpp codigo/informacionArticuloAgregado.cpp codigo/informacionFormularioContacto.cpp codigo/login.cpp codigo/liginRegistro.cpp codigo/registro.cpp codigo/resultadoBusqueda.cpp codigo/usuarioVerificado.cpp
	g++ `mysql_config --cflags --libs` codigo/agregarItem.cpp codigo/ConectorModular.cpp codigo/Checker.cpp -o ../cgi-bin/agregarItem.cgi -std=c++11
	g++ `mysql_config --cflags --libs` codigo/articulo.cpp codigo/ConectorModular.cpp Checker.cpp -o ../cgi-bin/articulo.cgi -std=c++11
	g++ codigo/carritoCompra.cpp -o cgi-bin/carritoCompra.cgi
	g++ codigo/carritoCompraEmbed.cpp -o cgi-bin/carritoCompraEmbed.cgi
	g++ codigo/finalizarCompra.cpp -o cgi-bin/finalizarCompra.cgi
	g++ codigo/formularioArticulo.cpp -o cgi-bin/formularioArticulo.cgi
	g++ codigo/formularioContacto.cpp -o cgi-bin/formularioContacto.cgi
	g++ `mysql_config --cflags --libs` codigo/informacionArticuloAgregado.cpp codigo/ConectorModular.cpp codigo/Checker.cpp -o ../cgi-bin/informacionArticuloAgregado.cgi -std=c++11
	g++ `mysql_config --cflags --libs` codigo/informacionFormularioContacto.cpp codigo/ConectorModular.cpp codigo/Checker.cpp -o ../cgi-bin/informacionFormularioContacto.cgi -std=c++11
	g++ `mysql_config --cflags --libs` codigo/login.cpp codigo/ConectorModular.cpp codigo/Checker.cpp -o ../cgi-bin/login.cgi -std=c++11
	g++ `mysql_config --cflags --libs` codigo/registro.cpp codigo/ConectorModular.cpp codigo/Checker.cpp -o ../cgi-bin/registro.cgi -std=c++11
	g++ `mysql_config --cflags --libs` codigo/resultadoBusqueda.cpp codigo/ConectorModular.cpp codigo/Checker.cpp -o ../cgi-bin/resultadoBusqueda.cgi -std=c++11
	g++ codigo/usuarioVerificado.cpp -o cgi-bin/usuarioVerificado.cgi

clean:
	rm cgi-bin/agregarItem.cgi cgi-bin/articulo.cgi cgi-bin/carritoCompra.cgi cgi-bin/carritoCompraEmbed.cgi cgi-bin/finalizarCompra.cgi cgi-bin/formularioArticulo.cgi cgi-bin/formularioContacto.cgi cgi-bin/informacionArticuloAgregado.cgi cgi-bin/informacionFormularioContacto.cgi cgi-bin/login.cgi cgi-bin/loginRegistro.cgi cgi-bin/registro.cgi cgi-bin/resultadoBusqueda.cgi cgi-bin/usuarioVerificado.cgi