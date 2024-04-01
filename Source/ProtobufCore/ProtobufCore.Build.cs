using System.IO;
using UnrealBuildTool;

//ProtobufCore ����� ���� ��Ģ�� ����
public class ProtobufCore : ModuleRules
{
    //������. ��� ���� �ʱ�ȭ
    public ProtobufCore(ReadOnlyTargetRules Target) : base(Target)
    {
        //����� �ܺο��� ������ ���̺귯�� ��� ���
        Type = ModuleType.External;

        //Protocol Buffers ���̺귯���� ��� ���� ��ġ�� �����Ϸ����� �˷���
        PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));

        //���̺귯�� ������ ��ġ�� ��Ŀ�� ã�� �� �ֵ��� ����
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Lib", "Win64", "libprotobuf.lib"));

        //Protocol Buffers �ڵ忡�� RTTI�� ������� �ʵ��� ����.
        PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");

    }

}