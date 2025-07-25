% -------------------------------------------------------------------
%  Generated by MATLAB on 30-Aug-2023 10:39:50
%  MATLAB version: 9.4.0.813654 (R2018a)
% -------------------------------------------------------------------
                            

Sin_BreakPoint = mpt.Parameter;
Sin_BreakPoint.Value = [0 0.0635 0.1269 0.1904 0.2539 0.3173 0.3808 0.4443 ...
                        0.5077 0.5712 0.6347 0.6981 0.7616 0.8251 0.8885 ...
                        0.952 1.0155 1.0789 1.1424 1.2059 1.2693 1.3328 ...
                        1.3963 1.4597 1.5232 1.5867 1.6501 1.7136 1.7771 ...
                        1.8405 1.904 1.9675 2.0309 2.0944 2.1579 2.2213 ...
                        2.2848 2.3483 2.4117 2.4752 2.5387 2.6021 2.6656 ...
                        2.7291 2.7925 2.856 2.9195 2.9829 3.0464 3.1099 ...
                        3.1733 3.2368 3.3003 3.3637 3.4272 3.4907 3.5541 ...
                        3.6176 3.6811 3.7445 3.808 3.8715 3.9349 3.9984 ...
                        4.0619 4.1253 4.1888 4.2523 4.3157 4.3792 4.4427 ...
                        4.5061 4.5696 4.6331 4.6965 4.76 4.8235 4.8869 ...
                        4.9504 5.0139 5.0773 5.1408 5.2043 5.2677 5.3312 ...
                        5.3947 5.4581 5.5216 5.5851 5.6485 5.712 5.7755 ...
                        5.8389 5.9024 5.9659 6.0293 6.0928 6.1563 6.2197 ...
                        6.2832];
Sin_BreakPoint.CoderInfo.StorageClass = 'Custom';
Sin_BreakPoint.CoderInfo.Alias = '';
Sin_BreakPoint.CoderInfo.Alignment = -1;
Sin_BreakPoint.CoderInfo.CustomStorageClass = 'Global';
Sin_BreakPoint.CoderInfo.CustomAttributes.MemorySection = 'Default';
Sin_BreakPoint.CoderInfo.CustomAttributes.HeaderFile = '';
Sin_BreakPoint.CoderInfo.CustomAttributes.DefinitionFile = '';
Sin_BreakPoint.CoderInfo.CustomAttributes.Owner = '';
Sin_BreakPoint.CoderInfo.CustomAttributes.PersistenceLevel = 1;
Sin_BreakPoint.Description = '';
Sin_BreakPoint.DataType = 'single';
Sin_BreakPoint.Min = [];
Sin_BreakPoint.Max = [];
Sin_BreakPoint.DocUnits = '';

Sin_Table = mpt.Parameter;
Sin_Table.Value = [0 0.0635 0.1266 0.1893 0.2512 0.312 0.3717 0.4298 0.4862 ...
                   0.5406 0.5929 0.6428 0.6901 0.7346 0.7761 0.8146 0.8497 ...
                   0.8814 0.9096 0.9342 0.9549 0.9718 0.9848 0.9938 0.9989 ...
                   0.9999 0.9969 0.9898 0.9788 0.9638 0.945 0.9223 0.896 ...
                   0.866 0.8325 0.7958 0.7557 0.7127 0.6668 0.6182 0.567 ...
                   0.5137 0.4582 0.4009 0.342 0.2817 0.2203 0.158 0.095 ...
                   0.0317 -0.0317 -0.0951 -0.158 -0.2203 -0.2817 -0.3421 ...
                   -0.4009 -0.4582 -0.5137 -0.567 -0.6182 -0.6668 -0.7127 ...
                   -0.7558 -0.7958 -0.8326 -0.866 -0.896 -0.9223 -0.945 ...
                   -0.9639 -0.9788 -0.9898 -0.9969 -0.9999 -0.9989 -0.9938 ...
                   -0.9848 -0.9718 -0.9549 -0.9342 -0.9096 -0.8814 -0.8497 ...
                   -0.8146 -0.7761 -0.7346 -0.6901 -0.6428 -0.5929 -0.5406 ...
                   -0.4862 -0.4298 -0.3716 -0.312 -0.2512 -0.1892 -0.1265 ...
                   -0.0634 0];
Sin_Table.CoderInfo.StorageClass = 'Custom';
Sin_Table.CoderInfo.Alias = '';
Sin_Table.CoderInfo.Alignment = -1;
Sin_Table.CoderInfo.CustomStorageClass = 'Global';
Sin_Table.CoderInfo.CustomAttributes.MemorySection = 'Default';
Sin_Table.CoderInfo.CustomAttributes.HeaderFile = '';
Sin_Table.CoderInfo.CustomAttributes.DefinitionFile = '';
Sin_Table.CoderInfo.CustomAttributes.Owner = '';
Sin_Table.CoderInfo.CustomAttributes.PersistenceLevel = 1;
Sin_Table.Description = '';
Sin_Table.DataType = 'fixdt(1,16,14)';
Sin_Table.Min = [];
Sin_Table.Max = [];
Sin_Table.DocUnits = '';

Cos_Table = mpt.Parameter;
Cos_Table.Value = [1 0.998 0.992 0.9819 0.9679 0.9501 0.9284 0.9029 0.8739 ...
                   0.8413 0.8052 0.7661 0.7237 0.6785 0.6306 0.5801 0.5272 ...
                   0.4723 0.4154 0.3569 0.2969 0.2358 0.1736 0.1109 0.0476 ...
                   -0.0159 -0.0792 -0.1423 -0.2048 -0.2664 -0.3271 -0.3864 ...
                   -0.444 -0.5 -0.554 -0.6056 -0.6549 -0.7015 -0.7452 -0.7861 ...
                   -0.8237 -0.858 -0.8888 -0.9161 -0.9397 -0.9595 -0.9754 ...
                   -0.9874 -0.9955 -0.9995 -0.9995 -0.9955 -0.9874 -0.9754 ...
                   -0.9595 -0.9397 -0.9161 -0.8888 -0.858 -0.8237 -0.786 ...
                   -0.7452 -0.7015 -0.6549 -0.6056 -0.5539 -0.5 -0.444 ...
                   -0.3864 -0.3271 -0.2664 -0.2048 -0.1423 -0.0792 -0.0159 ...
                   0.0476 0.1109 0.1736 0.2358 0.297 0.3569 0.4154 0.4723 ...
                   0.5272 0.5801 0.6306 0.6785 0.7237 0.7661 0.8053 0.8413 ...
                   0.8739 0.9029 0.9284 0.9501 0.9679 0.9819 0.992 0.998 ...
                   1];
Cos_Table.CoderInfo.StorageClass = 'Custom';
Cos_Table.CoderInfo.Alias = '';
Cos_Table.CoderInfo.Alignment = -1;
Cos_Table.CoderInfo.CustomStorageClass = 'Global';
Cos_Table.CoderInfo.CustomAttributes.MemorySection = 'Default';
Cos_Table.CoderInfo.CustomAttributes.HeaderFile = '';
Cos_Table.CoderInfo.CustomAttributes.DefinitionFile = '';
Cos_Table.CoderInfo.CustomAttributes.Owner = '';
Cos_Table.CoderInfo.CustomAttributes.PersistenceLevel = 1;
Cos_Table.Description = '';
Cos_Table.DataType = 'fixdt(1,16,14)';
Cos_Table.Min = [];
Cos_Table.Max = [];
Cos_Table.DocUnits = '';

