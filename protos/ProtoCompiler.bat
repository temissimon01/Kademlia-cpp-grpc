@echo on

set "workdir=%cd%"

FOR /F "tokens=* USEBACKQ" %%F IN (`where.exe /F "grpc_cpp_plugin"`) DO (
	SET pluginpath=%%F
	BREAK
)

for /r %%i in (*.proto) do protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=%pluginpath% --proto_path=%workdir% %%i